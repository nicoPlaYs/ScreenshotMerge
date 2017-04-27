#include "include/windows/settingswindow.h"



// Constructor
SettingsWindow::SettingsWindow() : QDialog()
{
    this->settings = new QSettings(this);

    // Creation of the layout of the window
    layout = new QGridLayout(this);
    layout->setVerticalSpacing(10);

        // Image quality
        labelImageQuality = new QLabel(tr("Image Quality :"), this);

        sliderImageQuality = new QSlider(Qt::Horizontal, this);
        sliderImageQuality->setRange(1, 100);
        sliderImageQuality->setValue(this->settings->value("SettingsWindow/imageQuality", 85).toInt());

        spinBoxImageQuality = new QSpinBox(this);
        spinBoxImageQuality->setRange(1, 100);
        spinBoxImageQuality->setValue(this->sliderImageQuality->value());
        spinBoxImageQuality->setFixedWidth(35);
        QObject::connect(spinBoxImageQuality, SIGNAL(valueChanged(int)), sliderImageQuality, SLOT(setValue(int)));
        QObject::connect(sliderImageQuality, SIGNAL(valueChanged(int)), spinBoxImageQuality, SLOT(setValue(int)));

    layout->addWidget(labelImageQuality, 0, 0, 1, 1);
    layout->addWidget(sliderImageQuality, 0, 1, 1, 1);
    layout->addWidget(spinBoxImageQuality, 0, 2, 1, 1);

        // Default directory
        labelDefaultDirectory = new QLabel(tr("Default directory : "), this);
        lineEditDefaultDirectory = new QLineEdit(this->settings->value("SettingsWindow/defaultDirectory", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)).toString(), this);
        lineEditDefaultDirectory->setDisabled(true);
        changeDefaultDirectory = new QPushButton(tr("..."), this);
        QObject::connect(changeDefaultDirectory, SIGNAL(clicked()), this, SLOT(openSelectDefaultDirectory()));

    layout->addWidget(labelDefaultDirectory, 1, 0, 1, 1);
    layout->addWidget(lineEditDefaultDirectory, 1, 1, 1, 1);
    layout->addWidget(changeDefaultDirectory, 1, 2, 1, 1);

        // Always use the default directory
        labelAlwaysUseDefaultDirectory = new QLabel(tr("Always use the default directory :"), this);
        checkBoxAlwaysUseDefaultDirectory = new QCheckBox(this);
        checkBoxAlwaysUseDefaultDirectory->setChecked(this->settings->value("SettingsWindow/alwaysUseDefaultDirectory", false).toBool());

    layout->addWidget(labelAlwaysUseDefaultDirectory, 2, 0, 1, 1);
    layout->addWidget(checkBoxAlwaysUseDefaultDirectory, 2, 1, 1, 2, Qt::AlignHCenter);

        // Start the program minimized with Windows
        labelStartWithWindows = new QLabel(tr("Launch the program minimized at startup : "), this);
        checkBoxStartWithWindows = new QCheckBox(this);

        // We verify if it's the right path for the program to launch on system startup
        QString pathApp = "\"" + QCoreApplication::applicationFilePath() + "\" -minimized";
        pathApp.replace("/", "\\");
        QSettings startup("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        if(startup.value("Screenshot Merge", QString()).toString() == pathApp)
        {
            checkBoxStartWithWindows->setChecked(true);
        }
        else
        {
            checkBoxStartWithWindows->setChecked(false);
        }

    layout->addWidget(labelStartWithWindows, 4, 0, 1, 1);
    layout->addWidget(checkBoxStartWithWindows, 4, 1, 1, 2, Qt::AlignHCenter);

        // Minimize the window to the system tray
        labelMinimizeTray = new QLabel(tr("Minimize to the system tray :"), this);
        checkBoxMinimizeTray = new QCheckBox(this);
        checkBoxMinimizeTray->setChecked(this->settings->value("SettingsWindow/minimizeTray", false).toBool());
        if(checkBoxStartWithWindows->isChecked())
        {
            checkBoxMinimizeTray->setChecked(true);
            checkBoxMinimizeTray->setDisabled(true);
        }
        QObject::connect(checkBoxStartWithWindows, SIGNAL(toggled(bool)), checkBoxMinimizeTray, SLOT(setChecked(bool)));
        QObject::connect(checkBoxStartWithWindows, SIGNAL(toggled(bool)), checkBoxMinimizeTray, SLOT(setDisabled(bool)));

    layout->addWidget(labelMinimizeTray, 5, 0, 1, 1);
    layout->addWidget(checkBoxMinimizeTray, 5, 1, 1, 2, Qt::AlignHCenter);

        // Validate or Cancel button
        validateOrCancel = new QWidget(this);
            layoutValidateOrCancel = new QHBoxLayout(validateOrCancel);
            layoutValidateOrCancel->setContentsMargins(0,20,0,0);

                buttonValidateChanges = new QPushButton(tr("Validate"), validateOrCancel);
                buttonValidateChanges->setDefault(true);
                QObject::connect(buttonValidateChanges, SIGNAL(clicked()), this, SLOT(validateChanges()));

                buttonCancelChanges = new QPushButton(tr("Cancel"), validateOrCancel);
                QObject::connect(buttonCancelChanges, SIGNAL(clicked()), this, SLOT(close()));

            layoutValidateOrCancel->addWidget(buttonValidateChanges);
            layoutValidateOrCancel->addWidget(buttonCancelChanges);

    layout->addWidget(validateOrCancel, 6, 0, 1, 3, Qt::AlignHCenter);


    // Configure the window
    this->setWindowTitle(tr("Settings"));
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->setWindowModality(Qt::ApplicationModal);
    this->show();
    this->setMinimumSize(this->size());
}



// Destructor
SettingsWindow::~SettingsWindow()
{

}



// Qt slots


// Open a dialog for the user to select the default directory
void SettingsWindow::openSelectDefaultDirectory()
{
    lineEditDefaultDirectory->setText(QFileDialog::getExistingDirectory(this, tr("Select your default directory"),
                                                                        this->settings->value("SettingsWindow/defaultDirectory",
                                                                        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)).toString()));
}


// Validate the chances
void SettingsWindow::validateChanges()
{
    // Update all the value of the user settings
    settings->setValue("SettingsWindow/imageQuality", sliderImageQuality->value());
    settings->setValue("SettingsWindow/defaultDirectory", lineEditDefaultDirectory->text());
    settings->setValue("SettingsWindow/alwaysUseDefaultDirectory", checkBoxAlwaysUseDefaultDirectory->isChecked());
    settings->setValue("SettingsWindow/minimizeTray", checkBoxMinimizeTray->isChecked());

    // Add or remove the program on the list of the programs to launch at the start of Windows
    QSettings startup("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if(checkBoxStartWithWindows->isChecked())
    {
        QString pathApp = "\"" + QCoreApplication::applicationFilePath() + "\" -minimized";
        pathApp.replace("/", "\\");
        startup.setValue("Screenshot Merge", pathApp);
    }
    else
    {
        startup.remove("Screenshot Merge");
    }

    // Then close the settings window
    this->close();
}
