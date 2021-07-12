# pragma once

#include <QPen>
#include <QQuickPaintedItem>

/**
 * @brief The QLineItem class is a QtQuick item used for drawing styled lines
 *
 * The item draws a line between two specified points and calculates its geometry
 * accordingly.
 *
 * Line drawing can be customized by setting various QPen properties.
 */
class QLineItem : public QQuickPaintedItem
{
    Q_OBJECT
        Q_PROPERTY(QPointF from READ getFrom WRITE setFrom NOTIFY fromChanged)
        Q_PROPERTY(QPointF to READ getTo WRITE setTo NOTIFY toChanged)
        Q_PROPERTY(qreal penWidth READ getPenWidth WRITE setPenWidth NOTIFY penWidthChanged)
        Q_PROPERTY(QColor penColor READ getPenColor WRITE setPenColor NOTIFY penColorChanged)
        Q_PROPERTY(Qt::PenStyle penStyle READ getPenStyle WRITE setPenStyle NOTIFY penStyleChanged)
        Q_PROPERTY(QVariantList penDashPattern READ getPenDashPattern WRITE setPenDashPattern NOTIFY penDashPatternChanged)

public:
    explicit QLineItem(QQuickItem* parent = 0);

    // QQuickPaintedItem interface
    void paint(QPainter* painter);

    void updatePolish();

    QPointF getFrom() const;
    void setFrom(const QPointF& from);

    QPointF getTo() const;
    void setTo(const QPointF& to);

    qreal getPenWidth() const;
    void setPenWidth(qreal penWidth);

    QColor getPenColor() const;
    void setPenColor(const QColor& penColor);

    Qt::PenStyle getPenStyle() const;
    void setPenStyle(Qt::PenStyle penStyle);

    QVariantList getPenDashPattern() const;
    void setPenDashPattern(const QVariantList& dashPattern);

Q_SIGNALS:
    void fromChanged();
    void toChanged();
    void penWidthChanged();
    void penColorChanged();
    void penStyleChanged();
    void penDashPatternChanged();

private:
    QPointF m_from;
    QPointF m_to;
    QPen m_pen;
};
