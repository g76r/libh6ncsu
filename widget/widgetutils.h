/* Copyright 2014-2016 Hallowyn and others.
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
#ifndef WIDGETUTILS_H
#define WIDGETUTILS_H

#include "libh6ncsu_global.h"

class QWidget;

class LIBH6NCSUSHARED_EXPORT WidgetUtils {
  WidgetUtils() = delete;

public:
  /** Convenience for activateWindow() + ensure visible + ensure raised. */
  static void activateAndShowWindow(QWidget *widget);
  /** activateAndShowWindow() + ensure the widget and its parent are visible in
   * every containers they belong to (set current indexes on QStackedWidgets and
   * QTabWidgets, etc.). */
  static void ensureWidgetIsVisible(QWidget *widget);
};

#endif // WIDGETUTILS_H
