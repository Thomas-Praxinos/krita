/*
 *  Copyright (c) 2013 Somsubhra Bairi <somsubhra.bairi@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; version 2 of the License, or(at you option)
 *  any later version..
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "onionskin_dock.h"

#include <kis_view2.h>
#include <kis_animation.h>
#include <kis_canvas2.h>
#include <kis_animation_doc.h>
#include <kis_animation_part.h>
#include <kis_config.h>
#include "kis_opacity_selector_view.h"

#include <klocale.h>
#include <KColorButton>

#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QColor>
#include <QCheckBox>
#include <QSpinBox>

OnionSkinDock::OnionSkinDock() : QDockWidget(i18n("Onion Skin")), m_canvas(0), m_animation(0)
{
    this->setMinimumSize(300,160);

    QLabel* activeLabel = new QLabel(this);
    activeLabel->setText("Active: ");
    activeLabel->setGeometry(100,20,50,20);

    KisConfig cfg;

    QCheckBox* activeCheckBox = new QCheckBox(this);
    activeCheckBox->setChecked(cfg.defOnionSkinningEnabled());
    activeCheckBox->setGeometry(150, 20, 20, 20);

    connect(activeCheckBox, SIGNAL(clicked(bool)), this, SLOT(enableOnionSkinning(bool)));

    QLabel* frameLabel = new QLabel(this);
    frameLabel->setText("Frames");
    frameLabel->setGeometry(130, 40, 50, 20);

    QSpinBox* previousFramesInput = new QSpinBox(this);
    previousFramesInput->setRange(0, 10);
    previousFramesInput->setValue(3);
    previousFramesInput->setGeometry(60,40,50,20);

    QSpinBox* nextFramesInput = new QSpinBox(this);
    nextFramesInput->setRange(0, 10);
    nextFramesInput->setValue(3);
    nextFramesInput->setGeometry(200, 40, 50, 20);

    QLabel* colorLabel = new QLabel(this);
    colorLabel->setText("Colors");
    colorLabel->setGeometry(130, 60, 50, 20);

    KColorButton* previousFramesColor = new KColorButton(this);
    previousFramesColor->setColor(QColor(Qt::red));
    previousFramesColor->setGeometry(60, 60,50, 20);

    KColorButton* nextFramesColor = new KColorButton(this);
    nextFramesColor->setColor(QColor(Qt::blue));
    nextFramesColor->setGeometry(200, 60, 50, 20);

    QLabel* opacityLabel = new QLabel(this);
    opacityLabel->setText("Opacity");
    opacityLabel->setGeometry(130, 80, 50, 20);

    KisOpacitySelectorView* previousOpacitySelectorView = new KisOpacitySelectorView(this, KisOpacitySelector::PREV_FRAMES_OPACITY_SELECTOR);
    previousOpacitySelectorView->setNumberOfFrames(previousFramesInput->value());
    previousOpacitySelectorView->setGeometry(20, 80, 105, 75);
    connect(previousFramesInput, SIGNAL(valueChanged(int)), previousOpacitySelectorView, SLOT(setNumberOfFrames(int)));

    KisOpacitySelectorView* nextOpacitySelectorView = new KisOpacitySelectorView(this, KisOpacitySelector::NEXT_FRAMES_OPACITY_SELECTOR);
    nextOpacitySelectorView->setNumberOfFrames(nextFramesInput->value());
    nextOpacitySelectorView->setGeometry(180, 80, 105, 75);
    connect(nextFramesInput, SIGNAL(valueChanged(int)), nextOpacitySelectorView, SLOT(setNumberOfFrames(int)));
}

void OnionSkinDock::setCanvas(KoCanvasBase *canvas)
{
    m_canvas = dynamic_cast<KisCanvas2*>(canvas);
    if(m_canvas && m_canvas->view() && m_canvas->view()->document() && m_canvas->view()->document()->documentPart()) {
        m_animation = dynamic_cast<KisAnimationPart*>(m_canvas->view()->document()->documentPart())->animation();
        if(m_animation) {

        }
    }
}

void OnionSkinDock::enableOnionSkinning(bool enable)
{
    m_animation->enableOnionSkinning(enable);
}
