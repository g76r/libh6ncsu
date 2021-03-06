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
#ifndef DTPGRAPHICSVIEW_H
#define DTPGRAPHICSVIEW_H

#include "libh6ncsu_global.h"
#include "enhancedgraphicsview.h"
#include "dtp/perspectivewidget.h"

class LIBH6NCSUSHARED_EXPORT DtpGraphicsView : public EnhancedGraphicsView {
  Q_OBJECT
  Q_DISABLE_COPY(DtpGraphicsView)
  PerspectiveWidget *_perspectiveWidget;

public:
  explicit DtpGraphicsView(QWidget *parent = 0);
  void focusInEvent(QFocusEvent *event);
  void enterEvent(QEvent *event);
  void leaveEvent(QEvent *event);
  void setScene(QGraphicsScene *scene);

signals:
  /** Same as DtpGraphicsScene::selectedItemsChanged() but only emited when
   * this view has focus */
  void selectedItemsChanged(QStringList selectedItemsIds);
};

#endif // DTPGRAPHICSVIEW_H
