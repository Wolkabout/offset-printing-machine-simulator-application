#include "windowmanager.h"

WindowManager::WindowManager() { }

WindowManager::~WindowManager() {
    frameStack.~stack();
    frames.clear();
}

std::vector<std::shared_ptr<QFrame>> &WindowManager::getFrames()
{
    return frames;
}

int WindowManager::addFrame(std::shared_ptr<QFrame> frame)
{
    frames.push_back(frame);
    return frames.size() - 1;
}

void WindowManager::showFrame(int index)
{
    if (frameStack.size() > 0) {
        int index = frameStack.top();
        frames[index]->hide();
    }
    if (frameStack.size() == 0 || frameStack.top() != index) {
        frameStack.push(index);
    }
    frames[index]->show();
}

void WindowManager::showFrame(std::shared_ptr<QFrame> frame)
{
    for (int i = 0; i < frames.size(); i++) {
        if (frames[i] == frame) {
            showFrame(i);
        }
    }
}

void WindowManager::goBack()
{
    if (frameStack.size() > 0) {
        int topIndex = frameStack.top();
        frames[topIndex]->hide();
        frameStack.pop();
        if (frameStack.size() > 0) {
            int backIndex = frameStack.top();
            frames[backIndex]->show();
        }
    }
}

void WindowManager::hideEverything()
{
    if (frameStack.size() > 0) {
        int topIndex = frameStack.top();
        frames[topIndex]->hide();
    }
}

void WindowManager::clearStack()
{
    if (frameStack.size() > 0) {
        int topIndex = frameStack.top();
        frames[topIndex]->hide();
        frames.clear();
    }
}
