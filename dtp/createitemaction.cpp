#include "createitemaction.h"
#include "dtpdocumentmanager.h"
#include "dtpmainwindow.h"
#include <QMessageBox>

CreateItemAction::CreateItemAction(
    DtpDocumentManager *documentManager, QString idQualifier, QIcon icon,
    QString text, QObject *parent)
  : DtpAction(documentManager, parent) {
  setIcon(icon);
  setText(text);
  connect(this, &CreateItemAction::triggered, [=]() {
    QString reason;
    SharedUiItem newItem =
        documentManager->createNewItem(idQualifier, &reason);
    // on error, warn user
    if (newItem.isNull()) {
      QMessageBox::warning(
            DtpMainWindow::instance(),
            tr("Cannot create %1").arg(idQualifier),
            tr("Cannot create %1.\n\n%2").arg(idQualifier).arg(reason));
      return;
    }
    // if a target PerspectiveWidget exists try to start item edition through it
    PerspectiveWidget *pw = documentManager->targetManager()->targetWidget();
    if (pw && pw->startItemEdition(newItem.qualifiedId()))
      return;
    // otherwise, or if it failed, try through main window
    DtpMainWindow *mainWindow = DtpMainWindow::instance();
    if (mainWindow)
      mainWindow->startItemEdition(newItem.qualifiedId());
  });
}
