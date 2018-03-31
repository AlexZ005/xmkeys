#ifndef XMKEYS_ADVANCED_H
#define XMKEYS_ADVANCED_H
#include <QTableView>

class xmkeys_advanced : public QTableView {
     Q_OBJECT

public:
      xmkeys_advanced(QAbstractItemModel * model);
      ~xmkeys_advanced();

protected:
      void resizeEvent(QResizeEvent *event) override;
      QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
      void scrollTo (const QModelIndex & index, ScrollHint hint = EnsureVisible) override;

private:
      QTableView *frozenTableView;
      void init();
      void updateFrozenTableGeometry();

private slots:
      void updateSectionWidth(int logicalIndex, int oldSize, int newSize);
      void updateSectionHeight(int logicalIndex, int oldSize, int newSize);

};
#endif // XMKEYS_ADVANCED_H
