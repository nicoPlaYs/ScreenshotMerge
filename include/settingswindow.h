#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H



#include <QDialog>
#include <QSettings>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTranslator>
#include <QTextLine>
#include <QStandardPaths>
#include <QFileDialog>
#include <QCoreApplication>



// The window which change the settings of the program
class SettingsWindow : public QDialog
{
    Q_OBJECT

    // Variables
    private :
        // Settings of the user
        QSettings* settings;

        // Layout of the window
        QGridLayout* layout;

            // Image quality
            QLabel* labelImageQuality;
            QSlider* sliderImageQuality;
            QSpinBox* spinBoxImageQuality;

            // Default directory
            QLabel* labelDefaultDirectory;
            QLineEdit* lineEditDefaultDirectory;
            QPushButton* changeDefaultDirectory;

            // Always use the default directory
            QLabel* labelAlwaysUseDefaultDirectory;
            QCheckBox* checkBoxAlwaysUseDefaultDirectory;

            // Don't show the draw windows in merge mode
            QLabel* labelDontShowDrawWinMergeMode;
            QCheckBox* checkBoxDontShowDrawWindowMergeMode;

            // Start the program minimized with Windows
            QLabel* labelStartWithWindows;
            QCheckBox* checkBoxStartWithWindows;

            // Minimize the window to the system tray
            QLabel* labelMinimizeTray;
            QCheckBox* checkBoxMinimizeTray;

            // Validate or Cancel button
            QWidget* validateOrCancel;
                QHBoxLayout* layoutValidateOrCancel;
                    QPushButton* buttonValidateChanges;
                    QPushButton* buttonCancelChanges;

    // Constructor
    public :
        SettingsWindow(QSettings* settings);

    // Destructor
    public :
        ~SettingsWindow();

    // Qt slots
    public slots :
        // Open a dialog for the user to select the default directory
        void openSelectDefaultDirectory();

        // Validate the changes
        void validateChanges();
};



#endif // SETTINGSWINDOW_H
