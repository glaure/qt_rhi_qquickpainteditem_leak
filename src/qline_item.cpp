#include "qline_item.h"

#include <QDebug>
#include <QPainter>

QLineItem::QLineItem(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
    setAntialiasing(true);
}

void QLineItem::paint(QPainter* painter)
{
    QRectF rect = QRectF(m_from, m_to).normalized();
    QPointF origin = rect.topLeft();
    const qreal adjust = m_pen.widthF() / 2;
    origin -= QPointF(adjust, adjust);

    painter->setPen(m_pen);
    painter->drawLine(m_from - origin, m_to - origin);
}

QPointF QLineItem::getFrom() const
{
    return m_from;
}

void QLineItem::setFrom(const QPointF& from)
{
    if (from != m_from)
    {
        m_from = from;
        Q_EMIT fromChanged();
        polish();
    }
}

QPointF QLineItem::getTo() const
{
    return m_to;
}

void QLineItem::setTo(const QPointF& to)
{
    if (to != m_to)
    {
        m_to = to;
        Q_EMIT toChanged();
        polish();
    }
}

qreal QLineItem::getPenWidth() const
{
    return m_pen.widthF();
}

void QLineItem::setPenWidth(qreal penWidth)
{
    if (penWidth != m_pen.widthF())
    {
        m_pen.setWidthF(penWidth);
        Q_EMIT penWidthChanged();
        update();
    }
}

QColor QLineItem::getPenColor() const
{
    return m_pen.color();
}

void QLineItem::setPenColor(const QColor& penColor)
{
    if (penColor != m_pen.color())
    {
        m_pen.setColor(penColor);
        Q_EMIT penColorChanged();
        update();
    }
}

Qt::PenStyle QLineItem::getPenStyle() const
{
    return m_pen.style();
}

void QLineItem::setPenStyle(Qt::PenStyle penStyle)
{
    if (penStyle != m_pen.style())
    {
        m_pen.setStyle(penStyle);
        Q_EMIT penStyleChanged();
        update();
    }
}

QVariantList QLineItem::getPenDashPattern() const
{
    const QVector<qreal> dashPattern = m_pen.dashPattern();

    QVariantList result;
    result.reserve(dashPattern.count());
    for (int i = 0; i < dashPattern.count(); ++i)
    {
        result[i] = dashPattern[i];
    }

    return result;
}

void QLineItem::setPenDashPattern(const QVariantList& dashPattern)
{
    QVector<qreal> input(dashPattern.count());
    for (int i = 0; i < dashPattern.count(); ++i)
    {
        input[i] = dashPattern[i].toReal();
    }

    if (input != m_pen.dashPattern())
    {
        m_pen.setDashPattern(input);
        Q_EMIT penDashPatternChanged();
        update();
    }
}

void QLineItem::updatePolish()
{
    QRectF rect = QRectF(m_from, m_to).normalized();
    const qreal adjust = m_pen.widthF() / 2;
    // make sure that horizontal and vertical lines do not draw pixels before start or after end
    if (rect.height() == 0)
    {
        rect.adjust(0, -adjust, 0, adjust);
    }
    else if (rect.width() == 0)
    {
        rect.adjust(-adjust, 0, adjust, 0);
    }
    else
    {
        rect.adjust(-adjust, -adjust, adjust, adjust);
    }

    setX(rect.left());
    setY(rect.top());
    setWidth(rect.width());
    setHeight(rect.height());
}
