#include "dtptreeview.h"
#include "dtp/dtpdocumentmanager.h"
#include "modelview/shareduiitem.h"
#include <QtDebug>
#include "modelview/shareduiitemsmodel.h"

DtpTreeView::DtpTreeView(QWidget *parent) : EnhancedTreeView(parent) {
  connect(this, &QAbstractItemView::entered,
          this, &DtpTreeView::itemHovered);
  connect(this, SIGNAL(viewportEntered()),
          this, SLOT(setMouseoverTarget()));
  connect(this, &EnhancedTreeView::leaved,
          this, &DtpTreeView::clearMouseoverTarget);
}

void DtpTreeView::setPerspectiveWidget(PerspectiveWidget *widget) {
  _perspectiveWidget = widget;
}

void DtpTreeView::setModel(QAbstractItemModel *newModel) {
  SharedUiItemsModel *m = _proxyModelHelper.realModel();
  if (m) {
    disconnect(m, &SharedUiItemsModel::itemChanged,
               this, &DtpTreeView::itemChanged);
  }
  EnhancedTreeView::setModel(newModel);
  _proxyModelHelper.setApparentModel(newModel);
  m = _proxyModelHelper.realModel();
  if (m) {
    connect(m, &SharedUiItemsModel::itemChanged,
            this, &DtpTreeView::itemChanged);
  }
  setMouseTracking(newModel);
  if (underMouse())
    setMouseoverTarget();
}

void DtpTreeView::itemHovered(const QModelIndex &index) {
  QAbstractItemModel *m = model();
  QString id;
  if (m) {
    _mousePosition = index;
    id = m->data(index, SharedUiItem::QualifiedIdRole).toString();
  }
  setMouseoverTarget(id);
}

void DtpTreeView::setMouseoverTarget(QString itemId)  {
  if (itemId.isNull())
    _mousePosition = QPersistentModelIndex();
  TargetManager *tm = PerspectiveWidget::targetManager(_perspectiveWidget);
  if (tm) {
    QStringList itemIds;
    if (!itemId.isNull())
      itemIds.append(itemId);
    tm->setTarget(TargetManager::MouseOverTarget, _perspectiveWidget, itemIds);
  }
}

void DtpTreeView::clearMouseoverTarget() {
  _mousePosition = QPersistentModelIndex();
  TargetManager *tm = PerspectiveWidget::targetManager(_perspectiveWidget);
  if (tm)
    tm->setTarget(TargetManager::MouseOverTarget);
}

void DtpTreeView::selectionChanged(const QItemSelection &selected,
                                   const QItemSelection &deselected) {
  EnhancedTreeView::selectionChanged(selected, deselected);
  QAbstractItemModel *m = model();
  // LATER use a better way to identify rows than testing column 0, since this only works with selectionBehavior() == SelectRows
  if (m) {
    foreach(const QModelIndex &index, deselected.indexes()) {
      if (index.column() == 0) {
        _selectedItemsIds.removeAll(index.data(SharedUiItem::QualifiedIdRole)
                                    .toString());
      }
    }
    foreach(const QModelIndex &index, selected.indexes()) {
      QString id = index.data(SharedUiItem::QualifiedIdRole).toString();
      if (index.column() == 0 && !_selectedItemsIds.contains(id)) {
        _selectedItemsIds.append(id);
      }
    }
  }
  emit selectedItemsChanged(_selectedItemsIds);
  if (hasFocus()) {
    TargetManager *tm = PerspectiveWidget::targetManager(_perspectiveWidget);
    if (tm)
      tm->setTarget(_perspectiveWidget, _selectedItemsIds);
  }
}

void DtpTreeView::focusInEvent(QFocusEvent *event) {
  EnhancedTreeView::focusInEvent(event);
  TargetManager *tm = PerspectiveWidget::targetManager(_perspectiveWidget);
  if (tm) {
    tm->setTarget(_perspectiveWidget, _selectedItemsIds);
    // set mouseover target in case overed item's id has just changed (which is
    // the case when focus in event is received just after an item id widget
    // editor has been closed)
    QString id = mouseoverItemId();
    tm->setTarget(TargetManager::MouseOverTarget, _perspectiveWidget, id);
  }
}

void DtpTreeView::itemChanged(SharedUiItem newItem, SharedUiItem oldItem) {
  // Update current selection when an item id changes.
  if (!oldItem.isNull()) { // new items cannot already be targeted
    QString newId = newItem.qualifiedId(), oldId = oldItem.qualifiedId();
    if (oldId != newId) { // only handle events where id changed
      if (newItem.isNull()) { // item removed
        _selectedItemsIds.removeAll(oldId);
      } else { // item renamed
        for (int i = 0; i < _selectedItemsIds.size(); ++i) {
          QString &id = _selectedItemsIds[i];
          if (id == oldId) {
            id = newId;
          }
        }
      }
    }
  }
  // ensure new or modified item is visible
  if (!newItem.isNull()) {
    QModelIndex index = _proxyModelHelper.indexOf(newItem);
    if (index.isValid())
      scrollTo(index);
  }
}

void DtpTreeView::focusOutEvent(QFocusEvent *event) {
  EnhancedTreeView::focusOutEvent(event);
  TargetManager *tm = PerspectiveWidget::targetManager(_perspectiveWidget);
  if (tm)
    tm->setTarget();
}

QString DtpTreeView::mouseoverItemId() const {
  QAbstractItemModel *m = model();
  return _mousePosition.isValid() && m
      ? _mousePosition.data(SharedUiItem::QualifiedIdRole).toString()
      : QString();
}