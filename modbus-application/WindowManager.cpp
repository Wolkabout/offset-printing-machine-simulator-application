#include "WindowManager.h"

std::vector <std::shared_ptr<QFrame>>& WindowManager::getFrames()
{
    return m_frames;
}

WindowManager::WindowManager() {}

int WindowManager::addFrame(std::shared_ptr<QFrame> frame)
{
    m_frames.push_back(frame);
    return m_frames.size() - 1;
}

void WindowManager::showFrame(int index)
{
    if (m_frameStack.size() > 0)
    {
        int m_index = m_frameStack.top();
        m_frames[m_index]->hide();
    }
    if (m_frameStack.size() == 0 || m_frameStack.top() != index)
    {
        m_frameStack.push(index);
    }
    m_frames[index]->show();
}

void WindowManager::showFrame(std::shared_ptr<QFrame> frame)
{
    for (int i = 0; i < m_frames.size(); i++)
    {
        if (m_frames[i] == frame)
        {
            showFrame(i);
        }
    }
}

void WindowManager::goBack()
{
    if (m_frameStack.size() > 0)
    {
        int topIndex = m_frameStack.top();
        m_frames[topIndex]->hide();
        m_frameStack.pop();
        if (m_frameStack.size() > 0)
        {
            int backIndex = m_frameStack.top();
            m_frames[backIndex]->show();
        }
    }
}

void WindowManager::hideEverything()
{
    if (m_frameStack.size() > 0)
    {
        int topIndex = m_frameStack.top();
        m_frames[topIndex]->hide();
    }
}

void WindowManager::clearStack()
{
    if (m_frameStack.size() > 0)
    {
        int topIndex = m_frameStack.top();
        m_frames[topIndex]->hide();
        m_frames.clear();
    }
}

WindowManager::~WindowManager()
{
    m_frameStack.empty();
    m_frames.clear();
}
