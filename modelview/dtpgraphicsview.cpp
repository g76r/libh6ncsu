/* Copyright 2014-2015 Hallowyn and others.
 * This file is part of libh6ncsu, see <https://gitlab.com/g76r/libh6ncsu>.
 * Libh6ncsu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * Libh6ncsu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * You should have received a copy of the GNU Affero General Public License
 * along with libh6ncsu.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "dtpgraphicsview.h"
#include "dtp/targetmanager.h"
#include "dtpgraphicsscene.h"

DtpGraphicsView::DtpGraphicsView(QWidget *parent)
  : EnhancedGraphicsView(parent) {
  setFocusPolicy(Qt::StrongFocus);
}

void DtpGraphicsView::setScene(QGraphicsScene *scene) {
  setMouseTracking(scene);
  EnhancedGraphicsView::setScene(scene);
  DtpGraphicsScene *dgs = qobject_cast<DtpGraphicsScene*>(scene);
  _perspectiveWidget = dgs ? dgs->perspectiveWidget() : 0;
  if (dgs && hasFocus()) {
    TargetManager *tm = PerspectiveWidget::targetManager(_perspectiveWidget);
    if (tm)
      tm->setTarget(_perspectiveWidget, dgs->selectedItemsIds());
  }
}

void DtpGraphicsView::focusInEvent(QFocusEvent *event) {
  EnhancedGraphicsView::focusInEvent(event);
  DtpGraphicsScene *dgs = qobject_cast<DtpGraphicsScene*>(scene());
  TargetManager *tm = PerspectiveWidget::targetManager(_perspectiveWidget);
  if (dgs && tm)
    tm->setTarget(_perspectiveWidget, dgs->selectedItemsIds());
}

void DtpGraphicsView::enterEvent(QEvent *event) {
  EnhancedGraphicsView::enterEvent(event);
  TargetManager *tm = PerspectiveWidget::targetManager(_perspectiveWidget);
  if (tm)
    tm->setTarget(TargetManager::MouseOverTarget, _perspectiveWidget);
}

void DtpGraphicsView::leaveEvent(QEvent *event) {
  EnhancedGraphicsView::leaveEvent(event);
  TargetManager *tm = PerspectiveWidget::targetManager(_perspectiveWidget);
  if (tm)
    tm->setTarget(TargetManager::MouseOverTarget);
}
