#ifndef DTTTREEVIEW_H
#define DTTTREEVIEW_H

#include "enhancedtreeview.h"
#include "dtt/perspectivewidget.h"
#include "modelview/shareduiitem.h"
#include <QPersistentModelIndex>

class TargetManager;

/** Document-Target-Tool enabled TreeView, with features such as target
 * management according to widget focus, selection and mouse over. */
class LIBH6NCSUSHARED_EXPORT DttTreeView : public EnhancedTreeView {
  Q_OBJECT
  Q_DISABLE_COPY(DttTreeView)
  QPointer<PerspectiveWidget> _perspectiveWidget;
  QPersistentModelIndex _mousePosition;
  QStringList _selectedItemsIds;

public:
  explicit DttTreeView(QWidget *parent = 0);
  void setPerspectiveWidget(PerspectiveWidget *widget);
  void setModel(QAbstractItemModel *newModel);
  void focusInEvent(QFocusEvent *event);
  void focusOutEvent(QFocusEvent *event);
  //QStringList selectedItemsIds() const { return _selectedItemsIds; }
  //QPersistentModelIndex mousePosition() const { return _mousePosition; }

signals:
  void selectedItemsChanged(QStringList selectedItemsIds);

protected:
  void selectionChanged(const QItemSelection &selected,
                        const QItemSelection &deselected);

private slots:
  void itemHovered(const QModelIndex &index);
  void setMouseoverTarget(QString itemId = QString());
  void clearMouseoverTarget();
  void itemChanged(SharedUiItem newItem, SharedUiItem oldItem);

private:
  QString mouseoverItemId() const;
};

#endif // DTTTREEVIEW_H
