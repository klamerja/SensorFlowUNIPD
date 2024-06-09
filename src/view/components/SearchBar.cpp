#include "SearchBar.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QSvgWidget>
#include <QPalette>
#include <QColor>
#include <QSvgWidget>
#include <QToolButton>
#include <QIcon>
#include <QGraphicsDropShadowEffect>

SearchBar::SearchBar(){
    setStyleSheet("background-color: #FFFFFF; border-radius: 12px;");

    QHBoxLayout* hLayout=new QHBoxLayout;
    hLayout->setAlignment(Qt::AlignVCenter);
    setLayout(hLayout);

    QSvgWidget* searchIcon=new QSvgWidget(":/assets/SearchBar/Search.svg");
    searchIcon->setFixedSize(20,20);
    hLayout->addWidget(searchIcon);
    searchIcon->setAutoFillBackground(false);

    QLineEdit* searchEdit=new QLineEdit;
    searchEdit->setFrame(false);
    searchEdit->setFixedHeight(20);
    QFont searchEditFont(searchEdit->font());
    searchEditFont.setPointSize(14);
    searchEdit->setFont(searchEditFont);
    searchEdit->setPlaceholderText("Cerca...");
    hLayout->addWidget(searchEdit);

    searchEdit->setClearButtonEnabled(true);
    QSvgWidget clearBtn(":/assets/SearchBar/Clear.svg");
    QToolButton* clearBtnWidget=searchEdit->findChild<QToolButton*>();
    clearBtnWidget->setIcon(QPixmap(":/assets/SearchBar/Clear.svg"));

    connect(searchEdit, &QLineEdit::textChanged, [&](const QString& s){
        emit textChanged(s);
    });
}