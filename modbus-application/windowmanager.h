#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <memory>
#include <vector>
#include <stack>
#include <qframe.h>

class WindowManager
{
private:
    std::vector<std::shared_ptr<QFrame>> frames;
    std::stack<int> frameStack;
public:
    WindowManager();
    ~WindowManager();
    std::vector<std::shared_ptr<QFrame>> &getFrames();
    int addFrame(std::shared_ptr<QFrame>);
    void showFrame(int);
    void showFrame(std::shared_ptr<QFrame>);
    void goBack();
    void hideEverything();
    void clearStack();
};

#endif // WINDOWMANAGER_H
