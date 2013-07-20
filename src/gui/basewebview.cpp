#include <QStyleOptionFrameV3>

#include "core/basewebpage.h"
#include "gui/basewebview.h"


BaseWebView::BaseWebView(QWidget *parent)
  : QWebView(parent), m_page(new BaseWebPage(this)) {
  setPage(m_page);
  createConnections();
}

BaseWebView::~BaseWebView() {
}

void BaseWebView::onLoadFinished(bool ok) {
  // If page was not loaded, then display custom error page.
  if (!ok) {
    displayErrorPage();
  }
}

void BaseWebView::createConnections() {
  connect(this, &BaseWebView::loadFinished,
          this, &BaseWebView::onLoadFinished);
}

void BaseWebView::displayErrorPage() {
  // TODO: Add better custom error page.
  setHtml("error", url());
}

void BaseWebView::paintEvent(QPaintEvent *event) {
  QWebView::paintEvent(event);

  // Draw additional frame.
  QPainter painter(this);
  QStyleOptionFrameV3 style_option;
  int frame_shape = QFrame::Sunken & QFrame::Shape_Mask;

  style_option.init(this);
  style_option.frameShape = QFrame::Shape(int(style_option.frameShape) |
                                          QFrame::StyledPanel |
                                          frame_shape);
  style_option.rect = rect();
  style_option.lineWidth = 1;
  style_option.midLineWidth = 0;

  style()->drawControl(QStyle::CE_ShapedFrame, &style_option, &painter, this);
}
