/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef PANEL_H
#define PANEL_H

#include "settings.h"
#include <qwidget.h>

class QCheckBox;
class QComboBox;
class QSpinBox;
class QLineEdit;

class Panel: public QWidget
{
    Q_OBJECT

public:
    Panel( QWidget *parent = NULL );

    void setSettings( const Settings &);
    Settings settings() const;

Q_SIGNALS:
    void edited();

private:
    struct
    {
        QCheckBox *checkBox;
        QComboBox *positionBox;

    } d_legend;

    struct
    {
        QCheckBox *checkBox;
        QSpinBox *numColumnsBox;
        QComboBox *hAlignmentBox;
        QComboBox *vAlignmentBox;
        QComboBox *backgroundBox;
        QSpinBox *sizeBox;

    } d_legendItem;

    struct
    {
        QSpinBox *numCurves;
        QLineEdit *title;

    } d_curve;
};

#endif