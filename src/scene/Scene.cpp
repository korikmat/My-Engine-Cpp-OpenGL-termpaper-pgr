//
// Created by korikmat on 06.05.2024.
//
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <random>
#include <utility>

#include "glm/ext/matrix_transform.hpp"

#include "Scene.h"
#include "../graphics/models/Terrain.h"
#include "../class_factory/ClassFactory.h"
#include "../window/Events.h"
#include "../graphics/models/TVModel.h"
#include "../loaders/FileSaver.h"

void registerClasses() {
    REGISTER_CLASS(Model);
    REGISTER_CLASS(Terrain);
    REGISTER_CLASS(TVModel);
    REGISTER_CLASS(AnimationPoint);
}

Scene::Scene(std::string sceneName) {
    if (!sceneName.empty()) {
        this->sceneNameBin = sceneName;
    }
    cameras.push_back(std::make_shared<Camera>(freeIDs[0], glm::vec3(0.0f, 0.0f, 3.0f), 60.0f));
    cameras.back()->active = true;
    freeIDs[0]++;

    registerClasses();
    loadScene();
}

void Scene::saveScene() {
    FileSaver fileSaver(WRITE, sceneNameBin);
    if (!fileSaver.getStatus()) {
        std::cerr << "Failed to open file for writing!" << std::endl;
        return;
    }

    fileSaver.saveToFile(freeIDs);
    fileSaver.saveToFile(models.size());
    fileSaver.saveToFile(lightingSystem.lights.size());
    for (auto &pair: models) {
        auto model = pair.second;
        fileSaver.saveToFile(model->className);
        fileSaver.saveToFile(model->ID);
        fileSaver.saveToFile(model->path);
        fileSaver.saveToFile(model->position);
        fileSaver.saveToFile(model->quatRotation);
        fileSaver.saveToFile(model->scale);
        fileSaver.saveToFile(model->calculateShadow);
        fileSaver.saveToFile(model->animated);
        fileSaver.saveToFile(model->animationType);
    }
    for (auto &light: lightingSystem.lights) {
        fileSaver.saveToFile(light->ID);
        fileSaver.saveToFile(light->position);
        fileSaver.saveToFile(light->color);
        fileSaver.saveToFile(light->direction_angle);
    }
    fileSaver.saveToFile(lightingSystem.sun.direction);
    fileSaver.saveToFile(lightingSystem.sun.color);
    fileSaver.saveToFile(lightingSystem.sun.enabled);
    fileSaver.saveToFile(lightingSystem.fog.color);
    fileSaver.saveToFile(lightingSystem.fog.density);
    fileSaver.saveToFile(lightingSystem.fog.enabled);
    fileSaver.saveToFile(currCamera);
    fileSaver.saveToFile(cameras.size());
    for (auto &camera: cameras) {
        fileSaver.saveToFile(camera->ID);
        fileSaver.saveToFile(camera->position);
        fileSaver.saveToFile(camera->Xangle);
        fileSaver.saveToFile(camera->Yangle);
        fileSaver.saveToFile(camera->Zangle);
        fileSaver.saveToFile(camera->fov);
        fileSaver.saveToFile(camera->aspect);
        fileSaver.saveToFile(camera->perspective);
        fileSaver.saveToFile(camera->flipped);
        fileSaver.saveToFile(camera->lock);
        fileSaver.saveToFile(camera->speed);
        fileSaver.saveToFile(camera->selectionMode);
        fileSaver.saveToFile(camera->cameraDistance);
        fileSaver.saveToFile(camera->active);
        fileSaver.saveToFile(camera->quatRotation);
        fileSaver.saveToFile(camera->animated);
        fileSaver.saveToFile(camera->animationType);
    }

    fileSaver.saveToFile(animationPoints.size());
    for (auto &point: animationPoints) {
        fileSaver.saveToFile(point->ID);
        fileSaver.saveToFile(point->position);
        fileSaver.saveToFile(point->quatRotation);
        fileSaver.saveToFile(point->path);
        fileSaver.saveToFile(point->className);
        fileSaver.saveToFile(point->hide);
    }
    std::cout << "Scene saved to file successfully\n";
}

void Scene::loadScene() {
    FileSaver fileSaver(READ, sceneNameBin);
    if (!fileSaver.getStatus()) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        return;
    }

    fileSaver.loadFromFile(freeIDs);
    size_t modelsCount, lightsCount;
    fileSaver.loadFromFile(modelsCount);
    fileSaver.loadFromFile(lightsCount);

    std::vector<ModelPtr> copiedModels;
    std::unordered_map<std::string, size_t> modelsLoaded;
    for (size_t idx = 0; idx < modelsCount; idx++) {
        std::string className;
        size_t ID;
        std::string path;
        glm::vec3 position, scale;
        glm::quat quatRotation;
        bool calculateShadow, animated, animationType;

        fileSaver.loadFromFile(className);
        fileSaver.loadFromFile(ID);
        fileSaver.loadFromFile(path);
        fileSaver.loadFromFile(position);
        fileSaver.loadFromFile(quatRotation);
        fileSaver.loadFromFile(scale);
        fileSaver.loadFromFile(calculateShadow);
        fileSaver.loadFromFile(animated);
        fileSaver.loadFromFile(animationType);

        if (modelsLoaded.find(path) == modelsLoaded.end()) {
            modelsLoaded[path] = ID;
            std::cout << "Creating original object with ID: " << ID << std::endl;
            models[ID] = ClassFactory::instance().create(className, path, ID);
            std::cout << "Object with path " << path << " loaded\n" << std::endl;
        } else {
            std::cout << "Object with path " << path << " already loaded" << std::endl;
            std::cout << "Creating " << ID << " copy of object with ID " << modelsLoaded[path] << std::endl;
            models[ID] = models[modelsLoaded[path]]->copy(ID);
            models[ID]->parent = models[modelsLoaded[path]];
        }
        models[ID]->className = className;
        models[ID]->position = position;
        models[ID]->quatRotation = quatRotation;
        models[ID]->scale = scale;
        models[ID]->calculateShadow = calculateShadow;
        models[ID]->animated = animated;
        models[ID]->animationType = animationType;
        if (models[ID]->className == GET_CLASS_NAME(TVModel)) {
            TVs.push_back(std::dynamic_pointer_cast<TVModel>(models[ID]));
        }
    }
    for (size_t idx = 0; idx < lightsCount; idx++) {
        size_t ID;
        glm::vec3 position;
        glm::vec3 color;
        glm::vec4 direction_angle;
        fileSaver.loadFromFile(ID);
        fileSaver.loadFromFile(position);
        fileSaver.loadFromFile(color);
        fileSaver.loadFromFile(direction_angle);
        lightingSystem.addSpotLight(ID, position, color, direction_angle);
    }

    fileSaver.loadFromFile(lightingSystem.sun.direction);
    fileSaver.loadFromFile(lightingSystem.sun.color);
    fileSaver.loadFromFile(lightingSystem.sun.enabled);

    fileSaver.loadFromFile(lightingSystem.fog.color);
    fileSaver.loadFromFile(lightingSystem.fog.density);
    fileSaver.loadFromFile(lightingSystem.fog.enabled);

    fileSaver.loadFromFile(currCamera);

    cameras.clear();
    size_t camerasCount;
    fileSaver.loadFromFile(camerasCount);
    for (size_t idx = 0; idx < camerasCount; idx++) {
        size_t ID;
        glm::vec3 position;
        glm::quat quatRotation;
        float Xangle, Yangle, Zangle, fov, aspect;
        bool perspective, flipped, lock, selectionMode, active, animated, animationType;
        float speed, cameraDistance;

        fileSaver.loadFromFile(ID);
        fileSaver.loadFromFile(position);
        fileSaver.loadFromFile(Xangle);
        fileSaver.loadFromFile(Yangle);
        fileSaver.loadFromFile(Zangle);
        fileSaver.loadFromFile(fov);
        fileSaver.loadFromFile(aspect);
        fileSaver.loadFromFile(perspective);
        fileSaver.loadFromFile(flipped);
        fileSaver.loadFromFile(lock);
        fileSaver.loadFromFile(speed);
        fileSaver.loadFromFile(selectionMode);
        fileSaver.loadFromFile(cameraDistance);
        fileSaver.loadFromFile(active);
        fileSaver.loadFromFile(quatRotation);
        fileSaver.loadFromFile(animated);
        fileSaver.loadFromFile(animationType);

        cameras.push_back(std::make_shared<Camera>(ID, position, fov));
        cameras.back()->Xangle = Xangle;
        cameras.back()->Yangle = Yangle;
        cameras.back()->Zangle = Zangle;
        cameras.back()->aspect = aspect;
        cameras.back()->perspective = perspective;
        cameras.back()->flipped = flipped;
        cameras.back()->lock = lock;
        cameras.back()->speed = speed;
        cameras.back()->selectionMode = selectionMode;
        cameras.back()->cameraDistance = cameraDistance;
        cameras.back()->active = active;
        cameras.back()->quatRotation = quatRotation;
        cameras.back()->animated = animated;
        cameras.back()->animationType = animationType;
        cameras.back()->updateVectors();
    }

    size_t animationPointsCount;
    fileSaver.loadFromFile(animationPointsCount);
    AnimationPointPtr animationPoint;
    for (size_t idx = 0; idx < animationPointsCount; idx++) {
        size_t ID;
        glm::vec3 position;
        glm::quat quatRotation;
        std::string path, className;
        bool hide;
        fileSaver.loadFromFile(ID);
        fileSaver.loadFromFile(position);
        fileSaver.loadFromFile(quatRotation);
        fileSaver.loadFromFile(path);
        fileSaver.loadFromFile(className);
        fileSaver.loadFromFile(hide);
        if (idx == 0) {
            animationPoint = std::make_shared<AnimationPoint>(path, ID);
        } else {
            animationPoint = std::dynamic_pointer_cast<AnimationPoint>(animationPoints.back()->copy(ID));
            if (animationPoints.back()->parent == nullptr) {
                animationPoint->parent = animationPoints.back();
            } else {
                animationPoint->parent = animationPoints.back()->parent;
            }
        }

        animationPoints.push_back(animationPoint);
        animationPoints.back()->position = position;
        animationPoints.back()->quatRotation = quatRotation;
        animationPoints.back()->className = className;
        animationPoints.back()->hide = hide;
    }

    std::cout << "\nScene loaded from file successfully\n" << std::endl;
}

void Scene::update(float deltaTime) {
    if (Events::keyboardJustPressed(GLFW_KEY_ESCAPE)) {
        Window::setWindowShouldClose(true);
    }
    if (Events::keyboardJustPressed(GLFW_KEY_F1)) {
        std::string sceneName = Window::openFileSaverDialog();
        if (!sceneName.empty()) {
            this->sceneNameBin = sceneName;
            saveScene();
        }
    }
    if (Events::keyboardJustPressed(GLFW_KEY_F2)) {
        std::string sceneName = Window::openFileSelectionDialog();
        if (!sceneName.empty()) {
            saveScene();
            this->sceneNameBin = sceneName;
            loadScene();
        }
    }

    if (Events::keyboardJustPressed(GLFW_KEY_TAB)) {
        Events::cursorLocked = !Events::cursorLocked;
        std::cout << "Cursor locked: " << Events::cursorLocked << std::endl;
        if (Events::cursorLocked) {
            glfwSetCursorPos(Window::window, (double) Window::WIDTH / 2, (double) Window::HEIGHT / 2);
            glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    if (Events::keyboardJustPressed(GLFW_KEY_1)) {
        std::string szFile;
        szFile = Window::openFileSelectionDialog();
        if (!szFile.empty()) {
            size_t objCurrID;
            if (freeIDs.size() > 1) {
                objCurrID = freeIDs.back();
                freeIDs.pop_back();
            } else {
                objCurrID = freeIDs[0];
                freeIDs[0]++;
            }
            models[objCurrID] = std::make_shared<Model>(szFile, objCurrID);
            models[objCurrID]->className = GET_CLASS_NAME(Model);
            models[objCurrID]->position = cameras[currCamera]->position + 3.0f * cameras[currCamera]->front;
        } else {
            std::cout << "File selection cancelled." << std::endl;
        }
    }
    if (Events::keyboardJustPressed(GLFW_KEY_2)) {
        std::string szFile;
        szFile = Window::openFileSelectionDialog();
        if (!szFile.empty()) {
            size_t objCurrID;
            if (freeIDs.size() > 1) {
                objCurrID = freeIDs.back();
                freeIDs.pop_back();
            } else {
                objCurrID = freeIDs[0];
                freeIDs[0]++;
            }
            models[objCurrID] = std::make_shared<Terrain>(szFile, objCurrID);
            models[objCurrID]->className = GET_CLASS_NAME(Terrain);
            models[objCurrID]->position = cameras[currCamera]->position + 3.0f * cameras[currCamera]->front;
        } else {
            std::cout << "File selection cancelled." << std::endl;
        }
    }
    if (Events::keyboardJustPressed(GLFW_KEY_3)) {
        float red = lightingSystem.getRandomColor();
        float green = lightingSystem.getRandomColor();
        float blue = lightingSystem.getRandomColor();
        size_t objCurrID;
        if (freeIDs.size() > 1) {
            objCurrID = freeIDs.back();
            freeIDs.pop_back();
        } else {
            objCurrID = freeIDs[0];
            freeIDs[0]++;
        }
        lightingSystem.addPointLight(objCurrID, cameras[currCamera]->position + 3.0f * cameras[currCamera]->front,
                                     glm::vec3(red, green, blue));
    }
    if (Events::keyboardJustPressed(GLFW_KEY_4)) {
        float red = lightingSystem.getRandomColor();
        float green = lightingSystem.getRandomColor();
        float blue = lightingSystem.getRandomColor();

        size_t objCurrID;
        if (freeIDs.size() > 1) {
            objCurrID = freeIDs.back();
            freeIDs.pop_back();
        } else {
            objCurrID = freeIDs[0];
            freeIDs[0]++;
        }
        lightingSystem.addSpotLight(objCurrID, cameras[currCamera]->position + 3.0f * cameras[currCamera]->front,
                                    glm::vec3(red, green, blue), glm::vec4(-1.0, 0.0, 0.0, 40.0));
    }
    if (Events::keyboardJustPressed(GLFW_KEY_5)) {
        size_t objCurrID;
        if (freeIDs.size() > 1) {
            objCurrID = freeIDs.back();
            freeIDs.pop_back();
        } else {
            objCurrID = freeIDs[0];
            freeIDs[0]++;
        }
        models[objCurrID] = std::make_shared<TVModel>("res/tv/tv.obj", objCurrID);
        models[objCurrID]->className = GET_CLASS_NAME(TVModel);
        models[objCurrID]->position = cameras[currCamera]->position + 3.0f * cameras[currCamera]->front;
        TVs.push_back(std::dynamic_pointer_cast<TVModel>(models[objCurrID]));
    }
    if (Events::keyboardJustPressed(GLFW_KEY_6)) {
        size_t objCurrID;
        if (freeIDs.size() > 1) {
            objCurrID = freeIDs.back();
            freeIDs.pop_back();
        } else {
            objCurrID = freeIDs[0];
            freeIDs[0]++;
        }
        cameras.push_back(
                std::make_shared<Camera>(objCurrID, cameras[currCamera]->position + 3.0f * cameras[currCamera]->front,
                                         60.0f));
        cameras.back()->Xangle = cameras[currCamera]->Xangle;
        cameras.back()->Yangle = cameras[currCamera]->Yangle;
        cameras.back()->Zangle = cameras[currCamera]->Zangle;
        cameras.back()->updateVectors();
    }
    if (Events::keyboardJustPressed(GLFW_KEY_7)) {
        size_t objCurrID;
        if (freeIDs.size() > 1) {
            objCurrID = freeIDs.back();
            freeIDs.pop_back();
        } else {
            objCurrID = freeIDs[0];
            freeIDs[0]++;
        }
        AnimationPointPtr animationPoint;
        if (!animationPoints.empty()) {
            animationPoint = std::dynamic_pointer_cast<AnimationPoint>(animationPoints.back()->copy(objCurrID));
            if (animationPoints.back()->parent == nullptr) {
                animationPoint->parent = animationPoints.back();
            } else {
                animationPoint->parent = animationPoints.back()->parent;
            }
        } else {
            animationPoint = std::make_shared<AnimationPoint>("res/animation/animation_point.obj", objCurrID);
        }
        animationPoints.push_back(animationPoint);
        animationPoints.back()->className = GET_CLASS_NAME(AnimationPoint);
        animationPoints.back()->position = cameras[currCamera]->position + 3.0f * cameras[currCamera]->front;
        animationPoints.back()->quatRotation = cameras[currCamera]->quatRotation;
    }

    if (Events::keyboardPressed(GLFW_KEY_LEFT_CONTROL)) {
        cameras[currCamera]->speed = 45.0f;
    } else {
        cameras[currCamera]->speed = 7.0f;
    }
    if (Events::keyboardPressed(GLFW_KEY_W)) {
        cameras[currCamera]->moveForward(deltaTime);

        for (auto &TV: TVs) {
            if (TV->isInside(cameras[currCamera]->position)) {
                cameras[currCamera]->moveBackward(deltaTime);
                break;
            }
        }
    }
    if (Events::keyboardPressed(GLFW_KEY_S)) {
        cameras[currCamera]->moveBackward(deltaTime);

        for (auto &TV: TVs) {
            if (TV->isInside(cameras[currCamera]->position)) {
                cameras[currCamera]->moveForward(deltaTime);
                break;
            }
        }
    }
    if (Events::keyboardPressed(GLFW_KEY_A)) {
        cameras[currCamera]->moveLeft(deltaTime);

        for (auto &TV: TVs) {
            if (TV->isInside(cameras[currCamera]->position)) {
                cameras[currCamera]->moveRight(deltaTime);
                break;
            }
        }
    }
    if (Events::keyboardPressed(GLFW_KEY_D)) {
        cameras[currCamera]->moveRight(deltaTime);

        for (auto &TV: TVs) {
            if (TV->isInside(cameras[currCamera]->position)) {
                cameras[currCamera]->moveLeft(deltaTime);
                break;
            }
        }
    }
    if (Events::keyboardPressed(GLFW_KEY_LEFT_SHIFT)) {
        cameras[currCamera]->moveDown(deltaTime);

        for (auto &TV: TVs) {
            if (TV->isInside(cameras[currCamera]->position)) {
                cameras[currCamera]->moveUp(deltaTime);
                break;
            }
        }
    }
    if (Events::keyboardPressed(GLFW_KEY_SPACE)) {
        cameras[currCamera]->moveUp(deltaTime);

        for (auto &TV: TVs) {
            if (TV->isInside(cameras[currCamera]->position)) {
                cameras[currCamera]->moveDown(deltaTime);
                break;
            }
        }
    }


//    cameras[currCamera]->rotate((float) Events::mouseDeltaY / (float) Window::HEIGHT,
//                                (float) Events::mouseDeltaX / (float) Window::WIDTH, 0.0f);

    cameras[currCamera]->applyRotation((float) -Events::mouseDeltaY / (float) Window::HEIGHT,
                                       (float) -Events::mouseDeltaX / (float) Window::WIDTH, 0.0f);

    if (Events::keyboardJustPressed(GLFW_KEY_L)) {
        cameras[currCamera]->lock = !cameras[currCamera]->lock;
    }

    if (Events::mouseJustPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        unsigned char pixelID;

        glReadPixels((int) (Window::WIDTH / 2), (int) (Window::HEIGHT / 2), 1, 1,
                     GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &pixelID);
        if (pixelID == 0) { // background was clicked
            std::cout << "clicked on background" << std::endl;
        } else { // object was clicked

            std::cout << "clicked on object with ID: " << (int) pixelID << std::endl;

            if (models.find(pixelID) != models.end()) {
                models[pixelID]->cameraDistance = glm::length(
                        models[pixelID]->position - cameras[currCamera]->position);
                models[pixelID]->selectionMode = !models[pixelID]->selectionMode;
            }
            for (auto &light: lightingSystem.lights) {
                if (light->ID == pixelID) {
                    light->cameraDistance = glm::length(light->position - cameras[currCamera]->position);
                    light->selectionMode = !light->selectionMode;
                }
            }
            for (auto &camera: cameras) {
                if (camera->ID == pixelID) {
                    std::cout << "Camera with ID " << camera->ID << " selected" << std::endl;
                    camera->cameraDistance = glm::length(camera->position - cameras[currCamera]->position);
                    camera->selectionMode = !camera->selectionMode;
                }
            }
            for (auto &animationPoint: animationPoints) {
                if (animationPoint->ID == pixelID) {
                    animationPoint->cameraDistance = glm::length(
                            animationPoint->position - cameras[currCamera]->position);
                    animationPoint->selectionMode = !animationPoint->selectionMode;
                }
            }

        }
    }

    if (Events::keyboardJustPressed(GLFW_KEY_RIGHT)) {
        cameras[currCamera++]->active = false;
        currCamera %= cameras.size();
        cameras[currCamera]->active = true;
        std::cout << "Camera switched to " << currCamera << std::endl;
    }

    if (Events::keyboardJustPressed(GLFW_KEY_E)) {

        unsigned char pixelID;
        glReadPixels((int) (Window::WIDTH / 2), (int) (Window::HEIGHT / 2), 1, 1,
                     GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &pixelID);
        std::cout << "\nInteracted with object with ID: " << (int) pixelID << "\n" << std::endl;
        if (models.find(pixelID) != models.end()) {
            models[pixelID]->isInteracted = true;
        }
        for (auto &light: lightingSystem.lights) {
            if (light->ID == pixelID) {
                light->isInteracted = true;
            }
        }
        for (auto &point: animationPoints) {
            if (point->ID == pixelID) {
                point->isInteracted = true;
            }
        }
    }

    if (Events::keyboardJustPressed(GLFW_KEY_F)) {
        std::cout << "Free ID: ";
        for (auto &IDs: freeIDs) {
            std::cout << " " << IDs << ", ";
        }
        std::cout << std::endl;
    }

    if (Events::keyboardJustPressed(GLFW_KEY_H)) {
        for (auto &animationPoint: animationPoints) {
            animationPoint->hide = !animationPoint->hide;
        }
    }

    if (Events::keyboardJustPressed(GLFW_KEY_0)) {
        lightingSystem.sun.enabled = !lightingSystem.sun.enabled;
    }

    if (Events::keyboardJustPressed(GLFW_KEY_9)) {
        lightingSystem.fog.enabled = !lightingSystem.fog.enabled;
    }

    for (auto &pair: models) {
        auto model = pair.second;
        model->projection = cameras[currCamera]->getProjection();
        model->view = cameras[currCamera]->getView();

        if (model->selectionMode) {
            if (model->rotationMode) {
                model->applyRotation((float) Events::mouseDeltaX / (float) Window::WIDTH, glm::vec3(0.0f, 1.0f, 0.0f));
                model->applyRotation((float) Events::mouseDeltaY / (float) Window::HEIGHT, cameras[currCamera]->right);
            }
            model->position = cameras[currCamera]->position + model->cameraDistance * cameras[currCamera]->front;
            model->scale += glm::vec3((float) Events::scrollY * 0.1f);
            cameras[currCamera]->lock = false;
            if (Events::mousePressed(GLFW_MOUSE_BUTTON_RIGHT)) {
                model->rotationMode = !model->rotationMode;
                cameras[currCamera]->lock = !cameras[currCamera]->lock;
            }
            if (Events::keyboardJustPressed(GLFW_KEY_O)) {
                std::cout << "Object with ID " << model->ID << " shadows!" << std::endl;
                model->calculateShadow = !model->calculateShadow;
            }
            if (Events::keyboardJustPressed(GLFW_KEY_C)) {
                size_t objCurrID;
                if (freeIDs.size() > 1) {
                    objCurrID = freeIDs.back();
                    freeIDs.pop_back();
                } else {
                    objCurrID = freeIDs[0];
                    freeIDs[0]++;
                }
                ModelPtr newModel = model->copy(objCurrID);
                models[objCurrID] = newModel;
                if (model->parent == nullptr) {
                    newModel->parent = model;
                } else {
                    newModel->parent = model->parent;
                }
                std::cout << "Object with ID " << model->ID << " copied" << std::endl;
            }
            if (Events::keyboardJustPressed(GLFW_KEY_BACKSPACE)) {
                freeIDs.push_back(model->ID);
                models.erase(model->ID);
                if (model->className == GET_CLASS_NAME(TVModel)) {
                    TVs.erase(std::find(TVs.begin(), TVs.end(), std::dynamic_pointer_cast<TVModel>(model)));
                }

                std::cout << "Object with ID " << model->ID << " deleted" << std::endl;
            }
            if (Events::keyboardJustPressed(GLFW_KEY_P)) {
                model->animated = !model->animated;
            }
            if (Events::keyboardJustPressed(GLFW_KEY_UP)) {
                model->animationType = !model->animationType;
            }

        }
        if (model->animated) {
            if (model->animationType == CATMULLROM_INTERPOLATION) {
                animator.catmullRom(model->position, model->quatRotation, animationPoints, deltaTime);
            } else if (model->animationType == LINEAR_INTERPOLATION) {
                animator.linear(model->position, model->quatRotation, animationPoints, deltaTime);
            }
        }
        model->update();

    }
    for (auto &light: lightingSystem.lights) {
        if (light->selectionMode) {
            light->scale += glm::vec3((float) Events::scrollY * 0.05f);
            if (Events::mouseJustPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
                float red = lightingSystem.getRandomColor();
                float green = lightingSystem.getRandomColor();
                float blue = lightingSystem.getRandomColor();
                light->color = glm::vec3(red, green, blue);
            }

            light->position = cameras[currCamera]->position + light->cameraDistance * cameras[currCamera]->front;
            light->direction_angle = glm::vec4(glm::normalize(glm::vec3(cameras[currCamera]->front)),
                                               light->direction_angle.w);
            lightingSystem.update();
        }
    }
    for (auto &camera: cameras) {
        if (camera->selectionMode) {
            camera->position = cameras[currCamera]->position + camera->cameraDistance * cameras[currCamera]->front;
            if (Events::keyboardJustPressed(GLFW_KEY_P)) {
                camera->animated = !camera->animated;
            }
            if (Events::keyboardJustPressed(GLFW_KEY_UP)) {
                camera->animationType = !camera->animationType;
            }
        }
        if (camera->animated) {
            if (camera->animationType == CATMULLROM_INTERPOLATION) {
                animator.catmullRom(camera->position, camera->quatRotation, animationPoints, deltaTime);
            } else if (camera->animationType == LINEAR_INTERPOLATION) {
                animator.linear(camera->position, camera->quatRotation, animationPoints, deltaTime);
            }
        }
        camera->update();
    }

    AnimationPointPtr deletedAnimationPoint = nullptr;
    AnimationPointPtr copiedAnimationPoint = nullptr;
    for (auto &animationPoint: animationPoints) {
        animationPoint->projection = cameras[currCamera]->getProjection();
        animationPoint->view = cameras[currCamera]->getView();
        if (animationPoint->selectionMode) {
            animationPoint->position =
                    cameras[currCamera]->position + animationPoint->cameraDistance * cameras[currCamera]->front;
            animationPoint->quatRotation = cameras[currCamera]->quatRotation;
            animationPoint->scale += glm::vec3((float) Events::scrollY * 0.1f);
            if (Events::keyboardJustPressed(GLFW_KEY_C)) {
                size_t objCurrID;
                if (freeIDs.size() > 1) {
                    objCurrID = freeIDs.back();
                    freeIDs.pop_back();
                } else {
                    objCurrID = freeIDs[0];
                    freeIDs[0]++;
                }
                ModelPtr newPoint = animationPoint->copy(objCurrID);
                copiedAnimationPoint = std::dynamic_pointer_cast<AnimationPoint>(newPoint);
                copiedAnimationPoint->selectionMode = true;
                animationPoint->selectionMode = false;
                if (animationPoint->parent == nullptr) {
                    copiedAnimationPoint->parent = animationPoint;
                } else {
                    copiedAnimationPoint->parent = animationPoint->parent;
                }
            }
            if (Events::keyboardJustPressed(GLFW_KEY_BACKSPACE)) {
                freeIDs.push_back(animationPoint->ID);
                deletedAnimationPoint = animationPoint;
            }

        }

        animationPoint->update();

    }
    if (copiedAnimationPoint != nullptr)
        animationPoints.push_back(copiedAnimationPoint);
    if (deletedAnimationPoint != nullptr)
        animationPoints.erase(std::find(animationPoints.begin(), animationPoints.end(), deletedAnimationPoint));
}

void Scene::draw(int fps) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::unordered_map<size_t, ModelPtr> modelsCopy = models;
    for (auto &animationPoint: animationPoints) {
        modelsCopy[animationPoint->ID] = animationPoint;

    }

    renderer.renderShadows(modelsCopy, cameras[currCamera], lightingSystem.lights.size());
    renderer.renderGeometry(modelsCopy, cameras, lightingSystem);
    renderer.renderLighting(cameras[currCamera], lightingSystem);
    renderer.renderSkybox(skybox, cameras[currCamera], lightingSystem);
    renderer.renderCrosshair(axesCrosshair, cameras[currCamera]);
    hudRenderer.drawDebug(fps);

    Window::swapBuffers();
    Events::pullEvents();
}