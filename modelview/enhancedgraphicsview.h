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
#ifndef ENHANCEDGRAPHICSVIEW_H
#define ENHANCEDGRAPHICSVIEW_H

#include <QGraphicsView>
#include "libh6ncsu_global.h"

/** Enhanced QListView
 *
 * Additionnal behaviours:
 * - bidirectional mouse grab scrolling on middle button
 * - zoom in and out on control + wheel up/wheel down
 *
 * Additionnal slots:
 * - fitAllInView(): zoom in or out to fit the current items bounding box
 * - zoomIn(), zoomOut(): zoom in or out by 20%
 */
class LIBH6NCSUSHARED_EXPORT EnhancedGraphicsView : public QGraphicsView {
  Q_OBJECT
private:
  bool _mouseDragScrolling, _mouseMoved;
  QPoint _lastPos;

public:
  explicit EnhancedGraphicsView(QWidget *parent);
  void wheelEvent(QWheelEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

public slots:
  void fitAllInView();
  void zoomIn();
  void zoomOut();
};

#endif // ENHANCEDGRAPHICSVIEW_H
