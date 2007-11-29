/*
 * This file is part of the KDE project
 *
 * Copyright (c) 2004 Cyrille Berger <cberger@cberger.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <stdlib.h>

#include <klocale.h>
#include <kcomponentdata.h>
#include <kgenericfactory.h>

#include <kis_convolution_painter.h>
#include "convolutionfilters.h"

KisKernelSP createKernel( qint32 i0, qint32 i1, qint32 i2,
                          qint32 i3, qint32 i4, qint32 i5,
                          qint32 i6, qint32 i7, qint32 i8,
                          qint32 factor, qint32 offset )
{
    KisKernelSP kernel = KisKernelSP(new KisKernel());
    kernel->width = 3;
    kernel->height = 3;

    kernel->factor = factor;
    kernel->offset = offset;

    kernel->data = new qint32[9];
    kernel->data[0] = i0;
    kernel->data[1] = i1;
    kernel->data[2] = i2;
    kernel->data[3] = i3;
    kernel->data[4] = i4;
    kernel->data[5] = i5;
    kernel->data[6] = i6;
    kernel->data[7] = i7;
    kernel->data[8] = i8;

    return kernel;
}



typedef KGenericFactory<KritaConvolutionFilters> KritaConvolutionFiltersFactory;
K_EXPORT_COMPONENT_FACTORY( kritaconvolutionfilters, KritaConvolutionFiltersFactory( "krita" ) )

KritaConvolutionFilters::KritaConvolutionFilters(QObject *parent, const QStringList &)
        : KParts::Plugin(parent)
{
    setComponentData(KritaConvolutionFiltersFactory::componentData());

    if (parent->inherits("KisFilterRegistry")) {
        KisFilterRegistry * manager = dynamic_cast<KisFilterRegistry *>(parent);
        manager->add(KisFilterSP(new KisGaussianBlurFilter()));
        manager->add(KisFilterSP(new KisSharpenFilter()));
        manager->add(KisFilterSP(new KisMeanRemovalFilter()));
        manager->add(KisFilterSP(new KisEmbossLaplascianFilter()));
        manager->add(KisFilterSP(new KisEmbossInAllDirectionsFilter()));
        manager->add(KisFilterSP(new KisEmbossHorizontalVerticalFilter()));
        manager->add(KisFilterSP(new KisEmbossVerticalFilter()));
        manager->add(KisFilterSP(new KisEmbossHorizontalFilter()));
        manager->add(KisFilterSP(new KisTopEdgeDetectionFilter()));
        manager->add(KisFilterSP(new KisRightEdgeDetectionFilter()));
        manager->add(KisFilterSP(new KisBottomEdgeDetectionFilter()));
        manager->add(KisFilterSP(new KisLeftEdgeDetectionFilter()));
    }
}

KritaConvolutionFilters::~KritaConvolutionFilters()
{
}

KisGaussianBlurFilter::KisGaussianBlurFilter()
    : KisConvolutionFilter(id(), CategoryBlur, i18n("&Gaussian Blur"))
{
    m_matrix = createKernel( 1, 2, 1, 2, 4, 2, 1, 2, 1, 16, 0);
    setSupportsPainting( true );
    setSupportsIncrementalPainting( false );

}


KisSharpenFilter::KisSharpenFilter()
    : KisConvolutionFilter(id(), CategoryEnhance, i18n("&Sharpen"))
{
    setSupportsPainting( true );
    setSupportsIncrementalPainting( false );

    m_matrix = createKernel( 0, -2, 0, -2, 11, -2, 0, -2, 0, 3, 0);
}

KisMeanRemovalFilter::KisMeanRemovalFilter()
    : KisConvolutionFilter(id(), CategoryEnhance, i18n("&Mean Removal"))
{
    setSupportsPainting( false );
    m_matrix = createKernel( -1, -1, -1, -1, 9, -1, -1, -1, -1, 1, 0);
}

KisEmbossLaplascianFilter::KisEmbossLaplascianFilter()
    : KisConvolutionFilter(id(), CategoryEmboss, i18n("Emboss Laplascian"))
{
    setSupportsPainting( false );
    m_matrix = createKernel( -1, 0, -1 , 0, 4, 0 , -1, 0, -1, 1, 127);
}

KisEmbossInAllDirectionsFilter::KisEmbossInAllDirectionsFilter()
    : KisConvolutionFilter(id(), CategoryEmboss, i18n("Emboss in All Directions"))
{
    setSupportsPainting( false );
    m_matrix = createKernel( -1, -1, -1 , -1, 8, -1 , -1, -1, -1, 1, 127);
}

KisEmbossHorizontalVerticalFilter::KisEmbossHorizontalVerticalFilter()
    : KisConvolutionFilter(id(), CategoryEmboss, i18n("Emboss Horizontal && Vertical"))
{
    setSupportsPainting( false );
    m_matrix = createKernel( 0, -1, 0 , -1, 4, -1 , 0, -1, 0, 1, 127);
}

KisEmbossVerticalFilter::KisEmbossVerticalFilter()
    : KisConvolutionFilter(id(), CategoryEmboss, i18n("Emboss Vertical Only"))
{
    setSupportsPainting( false );
    m_matrix = createKernel( 0, -1, 0 , 0, 2, 0 , 0, -1, 0, 1, 127);
}

KisEmbossHorizontalFilter::KisEmbossHorizontalFilter() :
    KisConvolutionFilter(id(), CategoryEmboss, i18n("Emboss Horizontal Only"))
{
    setSupportsPainting( false );
    m_matrix = createKernel( 0, 0, 0 , -1, 4, -1 , 0, 0, 0, 1, 127);
}

KisEmbossDiagonalFilter::KisEmbossDiagonalFilter()
    : KisConvolutionFilter(id(), CategoryEdgeDetection, i18n("Top Edge Detection"))
{
    setSupportsPainting( false );
    m_matrix = createKernel( -1, 0, -1 , 0, 4, 0 , -1, 0, -1, 1, 127);
}


KisTopEdgeDetectionFilter::KisTopEdgeDetectionFilter()
    : KisConvolutionFilter(id(), CategoryEdgeDetection, i18n("Top Edge Detection"))
{
    setSupportsPainting( false );
    m_matrix = createKernel( 1, 1, 1 , 0, 0, 0 , -1, -1, -1, 1, 127);

}

KisRightEdgeDetectionFilter::KisRightEdgeDetectionFilter()
    : KisConvolutionFilter(id(), CategoryEdgeDetection, i18n("Right Edge Detection"))
{
    setSupportsPainting( false );
    m_matrix = createKernel(  -1, 0, 1 , -1, 0, 1 , -1, 0, 1,  1, 127);
}

KisBottomEdgeDetectionFilter::KisBottomEdgeDetectionFilter() : KisConvolutionFilter(id(), CategoryEdgeDetection, i18n("Bottom Edge Detection"))
{
    setSupportsPainting( false );
    m_matrix = createKernel( -1, -1, -1 , 0, 0, 0 , 1, 1, 1, 1, 127);
}

KisLeftEdgeDetectionFilter::KisLeftEdgeDetectionFilter() : KisConvolutionFilter(id(), CategoryEdgeDetection, i18n("Left Edge Detection"))
{
    setSupportsPainting( false );
    m_matrix = createKernel( 1, 0, -1 , 1, 0, -1 , 1, 0, -1, 1, 127);
}
