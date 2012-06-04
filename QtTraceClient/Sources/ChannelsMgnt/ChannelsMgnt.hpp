#ifndef CHANNELSMGNT_HPP
#define CHANNELSMGNT_HPP

#include <QWidget>


class CChannelTreeItemDelegate;


namespace Ui {
class ChannelsMgnt;
}

class CChannelsMgnt : public QWidget
{
    Q_OBJECT
    
public:
    explicit CChannelsMgnt(QWidget *parent = 0);
    ~CChannelsMgnt();

    void Show( int x, int y );
    
protected:

    void LoadChannels();

private:
    Ui::ChannelsMgnt *ui;

    CChannelTreeItemDelegate*   m_pChannelTreeItemDelegate;
};

#endif // CHANNELSMGNT_HPP
