#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QAction>

class MainWindow;

class ActionManager
{
public:
    ActionManager();
    ~ActionManager();

    void setupAction(MainWindow * mainWindow);
    void retranslateUi(MainWindow *MainWindow);
    void setupShortcuts();

public:
    QAction *actionOpen;

    QAction *actionActualSize;
    QAction *actionToggleMaximize;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionToggleCheckerboard;
    QAction *actionRotateClockwise;

    QAction *actionPrevPicture;
    QAction *actionNextPicture;

    QAction *actionHorizontalFlip;
    QAction *actionFitInView;
    QAction *actionFitByWidth;
    QAction *actionCopyPixmap;
    QAction *actionCopyFilePath;
    QAction *actionPaste;
    QAction *actionToggleStayOnTop;
    QAction *actionToggleProtectMode;
    QAction *actionSettings;
    QAction *actionHelp;
    QAction *actionLocateInFileManager;
    QAction *actionProperties;
    QAction *actionQuitApp;
};

#endif // ACTIONMANAGER_H
