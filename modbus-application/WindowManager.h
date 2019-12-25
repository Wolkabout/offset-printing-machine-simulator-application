#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <memory>
#include <stack>
#include <vector>
#include <QFrame>

class WindowManager
{
private:
    std::vector<std::shared_ptr<QFrame>> m_frames;
    std::stack<int> m_frameStack;
public:
    std::vector<std::shared_ptr<QFrame>>& getFrames();

    WindowManager();

    ~WindowManager();

    int addFrame(std::shared_ptr<QFrame>);

    void showFrame(int);

    void showFrame(std::shared_ptr<QFrame>);

    void goBack();

    void hideEverything();

    void clearStack();
};

#endif // WINDOWMANAGER_H
