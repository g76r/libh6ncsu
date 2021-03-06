#ifndef ENHANCEDTEXTEDIT_H
#define ENHANCEDTEXTEDIT_H

#include <QTextEdit>
#include "libh6ncsu_global.h"

/** Enhanced QTextEdit
 *
 * Additionnal signals:
 * - editingFinished(): emited whenever enter/return is pressed or focus is lost
 *   (like QAbstractSpinBox::editingFinished()).
 */
class LIBH6NCSUSHARED_EXPORT EnhancedTextEdit : public QTextEdit {
  Q_OBJECT
  Q_DISABLE_COPY(EnhancedTextEdit)

public:
  explicit EnhancedTextEdit(QWidget *parent = 0) : QTextEdit(parent) { }

signals:
  void editingFinished();

protected:
  void keyPressEvent(QKeyEvent *event);
  void focusOutEvent(QFocusEvent *event);
};

#endif // ENHANCEDTEXTEDIT_H
