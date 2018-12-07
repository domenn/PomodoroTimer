//
// Created by domen on 7.12.2018.
//

#include "Notifications/notifications_api.h"

#include <QtWidgets/QFrame>
#include <QtCore/Qt>
#include <iostream>
#include <QGuiApplication>
#include <QScreen>
#include <QtWidgets/QVBoxLayout>
#include <QLabel>
#include <External/cpplogger/include/plog/Log.h>

//namespace my_qt_toasts {
//

std::ostream& operator<< (std::ostream& stream, const QSize& size) {
    stream << "W: " << size.width() << " H: " << size.height();
    return stream;
}

class QtoastItem : public QObject {
Q_OBJECT

public:
    void qt_toast(QString const& title, QString const& text) {
        auto* notifier = new QFrame;
        notifier->setAccessibleName("notifierFrame");
        notifier->setWindowFlags(
                Qt::Tool | Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        notifier->setFocusPolicy(Qt::NoFocus);
        notifier->setMinimumWidth(400);
        notifier->setMaximumWidth(400);

        auto* mainLayout = new QHBoxLayout;
        auto leftSpacer = new QWidget(notifier);
        leftSpacer->setFixedWidth(20);
        mainLayout->addWidget(leftSpacer, 1);

        auto* secondLayout = new QVBoxLayout;

        notifier->setLayout(mainLayout);

        auto label_title = new QLabel(title, notifier);
        LOG_VERBOSE << "Mate title label. Size: " << label_title->size();
        QFont f("Arial", 14, QFont::Bold);
        label_title->setFont(f);
        label_title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

        LOG_VERBOSE << "Title: set font and policy. Size: " << label_title->size();

        auto label_content = new QLabel(text, notifier);
        LOG_VERBOSE << "Content label: Make. Size: " << label_content->size();
        label_content->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        label_content->setWordWrap(true);
        label_content->setFixedSize(label_content->sizeHint());
        LOG_VERBOSE << "Content label: FixedSizeSet. Size: " << label_content->size();

        secondLayout->addWidget(label_title);
        secondLayout->addItem(new QSpacerItem(1, 8));
        secondLayout->addWidget(label_content);
        mainLayout->addLayout(secondLayout);
#define MACRO_SET_MARGINS setContentsMargins(8, 8, 8, 8)
        notifier->MACRO_SET_MARGINS;
        notifier->layout()->MACRO_SET_MARGINS;




//        notifier->setStyleSheet(// "QLabel { background-color: yellow };\n"
//                ".QFrame {\n"
//                "border: 1px solid black;\n"
//                "border-radius: 5px;\n"
//                // "background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #9dd53a, stop: .5 #a1d54f, stop: .51 #80c217, stop: 1 #7cbc0a);\n"
//                // "background-color: QLinearGradient( x1: 0, y1: 1, x2: 0.3, y2: 1, stop: 0 cyan, stop: 0.29 cyan, stop: 0.2901 white, stop: 1 white);\n"
//                "}"
//                ".QWidget {\n"
//                // "background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #9dd53a, stop: .5 #a1d54f, stop: .51 #80c217, stop: 1 #7cbc0a);\n"
//                "background-color: QLinearGradient( x1: 0, y1: 1, x2: 0.3, y2: 1, stop: 0 cyan, stop: 0.29 cyan, stop: 0.2901 white, stop: 1 white);\n"
//                "}"
//        );

        notifier->resize(notifier->minimumSizeHint());

        const QRect availableGeometry = QGuiApplication::primaryScreen()->availableGeometry();
        QRect geom = notifier->geometry();
        geom.moveBottomRight(availableGeometry.bottomRight() - QPoint(20, 20));

        notifier->setGeometry(geom);
        notifier->show();
    }
};

//}
//
//
//LibnNotificationButton libn_private_global_buttons[]{{}, {}, {}, {}};
//
//void libn_private_cb(NotifyNotification* notification,
//        char* action,
//        gpointer user_data) {
//    auto* struct_ptr = static_cast<LibnNotificationButton*>(user_data);
//    struct_ptr->libn_cb_function();
//}
//
void libn_show(const char* title, const char* text, LibnNotificationButton* buttons) {
    std::cout << "Sent notification: " << title << " with content: " << text << std::endl;
    QtoastItem itm;
    itm.qt_toast(title, text);
//    NotifyNotification* n = notify_notification_new(title, text, nullptr);
//    notify_notification_set_timeout(n, NOTIFY_EXPIRES_NEVER); // 10 seconds
//
//
//    char action_number = '0';
//    int index = 0;
//    while (buttons) {
//        libn_private_global_buttons[index].libn_cb_function = buttons->libn_cb_function;
//        notify_notification_add_action(n, (std::string("n_a") + action_number).c_str(), buttons->text, &libn_private_cb,
//                (gpointer*) (libn_private_global_buttons + index), nullptr);
//        ++action_number;
//        ++index;
//        buttons = buttons->next;
//    }
//
//    notify_notification_set_urgency(n, NOTIFY_URGENCY_NORMAL);
//
//    if (!notify_notification_show(n, 0)) {
//        std::cerr << "show has failed" << std::endl;
//    }
}
//

void libn_init(char const* app_name) {
    if (!plog::get()) {
        plog::init(plog::verbose);
    }
    LOG_VERBOSE << "QT Notification impl Inited";
}

#include "qt_notification_item.moc"