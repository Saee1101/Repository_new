#include "Button_TivanEX.h"

#include <QGraphicsDropShadowEffect>


Button_TivanEX::Button_TivanEX(QWidget *parent) : QPushButton(parent)
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setBlurRadius(10); // Set the blur radius for the shadow (adjust as needed)
    shadowEffect->setColor(QColor(0,0,0,100));// Set the color of the shadow

    shadowEffect->setOffset(-15,10); // Set the x and y offset of the shadow (adjust as needed)

    setGraphicsEffect(shadowEffect);// Apply the shadow effect to the button
}
