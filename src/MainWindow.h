// $Id$
// QtLobby released under the GPLv3, see COPYING for details.
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDialog>
#include <QSystemTrayIcon>
#include <QScriptEngine>
#include <QShortcut>

#include "ui_MainWidget.h"
#include "ui_AboutWidget.h"
#include "Settings.h"
#include "ConnectionWidget.h"
#include "CommandAssigner.h"
#include "Command.h"
#include "LobbyTabs.h"
#include "Users.h"
#include "Battles.h"
#include "InputLine.h"
#include "AudioBackend.h"
#include "UnitSyncLib.h"
#include "Preference.h"
//#include "MapSelector.h"
#include "StylesheetDialog.h"
#include "UserGroupsDialog.h"
#include "ScriptingDialog.h"
#include "BattleHost.h"
#include "BattleHostingDialog.h"
#include "HistoryDialog.h"
#include "DownloadsDialog.h"
#include "UserMenuBuilder.h"
#include "Notification.h"
#ifdef Q_WS_X11
    #include "DBusVisualNotificationBackend.h"
#else
    #include "TrayIconNotificationBackend.h"
#endif

#include "config.h"


class MainWindow : public QMainWindow, public Singleton<MainWindow>, private Ui::MainWindow {
    Q_OBJECT
    friend class Singleton<MainWindow>;
public:
    HistoryDialog* getHistoryDialog();
    ConnectionWidget* getConnectionDialog();

    QProcess qpSpring;
    QProcess qpSpringSetting;

private:
    MainWindow( QWidget* parent = 0 );
    ~MainWindow();
    void setupToolbar();
    void setupIcons();
    //the connection dialog
    ConnectionWidget* connectionWidget;
    //handles the interaction with the server and the authentication
    ServerContextState* serverContextState;
    //receives all commands, parses and assigns it to its destination module
    CommandAssigner* commandAssigner;
    //the tabs at the top, which contain the chat etc.
    LobbyTabs* lobbyTabs;

    AudioBackend audioBackend;
    UnitSyncLib* unitSyncLib;
    Preference* preference;
//    MapSelector* mapSelector;
    StylesheetDialog* stylesheetDialog;
    UserGroupsDialog* userGroupsDialog;
    ScriptingDialog* scriptingDialog;
    BattleHostingDialog *battleHostingDialog;
    DownloadsDialog* downloadsDialog;
    HistoryDialog* historyDialog;

    QToolButton* newTabButton;
    QLabel* battlesOnline;
    QLabel* usersOnline;
    QLabel* moderatorsOnline;
    QSystemTrayIcon* trayIcon;
    void createTrayIcon();
    QMenu* trayIconMenu;
    QAction* restoreAction;
    QColor regexpColor;
    QSettings* settings;
    bool inBattle;
    QByteArray lastState;
    QByteArray lastBattleState;
    QByteArray state;
    QScriptEngine scriptingEngine;
    QShortcut* nextTab;
    QShortcut* previousTab;
    QShortcut* closeTab;
    QShortcut* openNewTab;
    QShortcut* openNewTab2;
signals:
    void newTrayMessage(QString);
protected:
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent * event);
    void showEvent(QShowEvent * event);
private slots:
    void on_joinToolButton_clicked();
    void on_actionDownloads_triggered();
    void on_hostPushButton_clicked( bool closeFirst = false );
    void on_actionScripting_triggered();
    void about();
    void newUserTextInput();
    void toggleUserListVisible();
    void toggleShowHideMainWindow( QSystemTrayIcon::ActivationReason );
    void showConnectionWidget( bool );
    void showGroupsDialog();
    void showHistoryDialog();
    void setColorInducatorUsers( QString regExp );
    void setColorInducatorBattles( QString regExp );
    void startSpring();
    void startSpringSettings();
    void showStylesheetEditor();
    void onCurrentChanged(const QModelIndex & current, const QModelIndex & previous);
    void onChannelActivated();
    void onTeamPlayerSpecCountChanged(QString ratio);
    void onStatsChange(int users, int moderators);
    void onStatsChange(int battles);
    void connectionStatusChanged(ConnectionState);
    void onBlockInput(bool b);
    void onChangedToBattleTab();
    void onChangedFromBattleTab();
    void reloadPreferences();
    void copyUsualLayoutToBattle();
public slots:
    void changeEvent(QEvent *e);
    void playSample( SampleCollection sample );
    void sendTrayMessage( QString message, int milliseconds = 2000);
};

#endif
