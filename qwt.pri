################################################################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
################################################################


HEADERS += \
    $$QWT_SRC_DIR/qwt.h \
    $$QWT_SRC_DIR/qwt_abstract_scale_draw.h \
    $$QWT_SRC_DIR/qwt_bezier.h \
    $$QWT_SRC_DIR/qwt_clipper.h \
    $$QWT_SRC_DIR/qwt_color_map.h \
    $$QWT_SRC_DIR/qwt_column_symbol.h \
    $$QWT_SRC_DIR/qwt_date.h \
    $$QWT_SRC_DIR/qwt_date_scale_draw.h \
    $$QWT_SRC_DIR/qwt_date_scale_engine.h \
    $$QWT_SRC_DIR/qwt_dyngrid_layout.h \
    $$QWT_SRC_DIR/qwt_global.h \
    $$QWT_SRC_DIR/qwt_graphic.h \
    $$QWT_SRC_DIR/qwt_interval.h \
    $$QWT_SRC_DIR/qwt_interval_symbol.h \
    $$QWT_SRC_DIR/qwt_math.h \
    $$QWT_SRC_DIR/qwt_magnifier.h \
    $$QWT_SRC_DIR/qwt_null_paintdevice.h \
    $$QWT_SRC_DIR/qwt_painter.h \
    $$QWT_SRC_DIR/qwt_painter_command.h \
    $$QWT_SRC_DIR/qwt_panner.h \
    $$QWT_SRC_DIR/qwt_picker.h \
    $$QWT_SRC_DIR/qwt_picker_machine.h \
    $$QWT_SRC_DIR/qwt_pixel_matrix.h \
    $$QWT_SRC_DIR/qwt_point_3d.h \
    $$QWT_SRC_DIR/qwt_point_polar.h \
    $$QWT_SRC_DIR/qwt_round_scale_draw.h \
    $$QWT_SRC_DIR/qwt_scale_div.h \
    $$QWT_SRC_DIR/qwt_scale_draw.h \
    $$QWT_SRC_DIR/qwt_scale_engine.h \
    $$QWT_SRC_DIR/qwt_scale_map.h \
    $$QWT_SRC_DIR/qwt_spline.h \
    $$QWT_SRC_DIR/qwt_spline_basis.h \
    $$QWT_SRC_DIR/qwt_spline_parametrization.h \
    $$QWT_SRC_DIR/qwt_spline_local.h \
    $$QWT_SRC_DIR/qwt_spline_cubic.h \
    $$QWT_SRC_DIR/qwt_spline_pleasing.h \
    $$QWT_SRC_DIR/qwt_spline_polynomial.h \
    $$QWT_SRC_DIR/qwt_symbol.h \
    $$QWT_SRC_DIR/qwt_system_clock.h \
    $$QWT_SRC_DIR/qwt_text_engine.h \
    $$QWT_SRC_DIR/qwt_text_label.h \
    $$QWT_SRC_DIR/qwt_text.h \
    $$QWT_SRC_DIR/qwt_transform.h \
    $$QWT_SRC_DIR/qwt_widget_overlay.h

SOURCES += \
    $$QWT_SRC_DIR/qwt.cpp \
    $$QWT_SRC_DIR/qwt_abstract_scale_draw.cpp \
    $$QWT_SRC_DIR/qwt_bezier.cpp \
    $$QWT_SRC_DIR/qwt_clipper.cpp \
    $$QWT_SRC_DIR/qwt_color_map.cpp \
    $$QWT_SRC_DIR/qwt_column_symbol.cpp \
    $$QWT_SRC_DIR/qwt_date.cpp \
    $$QWT_SRC_DIR/qwt_date_scale_draw.cpp \
    $$QWT_SRC_DIR/qwt_date_scale_engine.cpp \
    $$QWT_SRC_DIR/qwt_dyngrid_layout.cpp \
    $$QWT_SRC_DIR/qwt_event_pattern.cpp \
    $$QWT_SRC_DIR/qwt_graphic.cpp \
    $$QWT_SRC_DIR/qwt_interval.cpp \
    $$QWT_SRC_DIR/qwt_interval_symbol.cpp \
    $$QWT_SRC_DIR/qwt_math.cpp \
    $$QWT_SRC_DIR/qwt_magnifier.cpp \
    $$QWT_SRC_DIR/qwt_null_paintdevice.cpp \
    $$QWT_SRC_DIR/qwt_painter.cpp \
    $$QWT_SRC_DIR/qwt_painter_command.cpp \
    $$QWT_SRC_DIR/qwt_panner.cpp \
    $$QWT_SRC_DIR/qwt_picker.cpp \
    $$QWT_SRC_DIR/qwt_picker_machine.cpp \
    $$QWT_SRC_DIR/qwt_pixel_matrix.cpp \
    $$QWT_SRC_DIR/qwt_point_3d.cpp \
    $$QWT_SRC_DIR/qwt_point_polar.cpp \
    $$QWT_SRC_DIR/qwt_round_scale_draw.cpp \
    $$QWT_SRC_DIR/qwt_scale_div.cpp \
    $$QWT_SRC_DIR/qwt_scale_draw.cpp \
    $$QWT_SRC_DIR/qwt_scale_map.cpp \
    $$QWT_SRC_DIR/qwt_scale_engine.cpp \
    $$QWT_SRC_DIR/qwt_spline.cpp \
    $$QWT_SRC_DIR/qwt_spline_basis.cpp \
    $$QWT_SRC_DIR/qwt_spline_parametrization.cpp \
    $$QWT_SRC_DIR/qwt_spline_local.cpp \
    $$QWT_SRC_DIR/qwt_spline_cubic.cpp \
    $$QWT_SRC_DIR/qwt_spline_pleasing.cpp \
    $$QWT_SRC_DIR/qwt_symbol.cpp \
    $$QWT_SRC_DIR/qwt_system_clock.cpp \
    $$QWT_SRC_DIR/qwt_text_engine.cpp \
    $$QWT_SRC_DIR/qwt_text_label.cpp \
    $$QWT_SRC_DIR/qwt_text.cpp \
    $$QWT_SRC_DIR/qwt_transform.cpp \
    $$QWT_SRC_DIR/qwt_widget_overlay.cpp


contains(QWT_CONFIG, QwtPlot) {

    HEADERS += \
        $$QWT_SRC_DIR/qwt_curve_fitter.h \
        $$QWT_SRC_DIR/qwt_spline_curve_fitter.h \
        $$QWT_SRC_DIR/qwt_weeding_curve_fitter.h \
        $$QWT_SRC_DIR/qwt_event_pattern.h \
        $$QWT_SRC_DIR/qwt_abstract_legend.h \
        $$QWT_SRC_DIR/qwt_legend.h \
        $$QWT_SRC_DIR/qwt_legend_data.h \
        $$QWT_SRC_DIR/qwt_legend_label.h \
        $$QWT_SRC_DIR/qwt_plot.h \
        $$QWT_SRC_DIR/qwt_plot_renderer.h \
        $$QWT_SRC_DIR/qwt_plot_curve.h \
        $$QWT_SRC_DIR/qwt_plot_dict.h \
        $$QWT_SRC_DIR/qwt_plot_directpainter.h \
        $$QWT_SRC_DIR/qwt_plot_graphicitem.h \
        $$QWT_SRC_DIR/qwt_plot_grid.h \
        $$QWT_SRC_DIR/qwt_plot_histogram.h \
        $$QWT_SRC_DIR/qwt_plot_item.h \
        $$QWT_SRC_DIR/qwt_plot_abstract_barchart.h \
        $$QWT_SRC_DIR/qwt_plot_barchart.h \
        $$QWT_SRC_DIR/qwt_plot_multi_barchart.h \
        $$QWT_SRC_DIR/qwt_plot_intervalcurve.h \
        $$QWT_SRC_DIR/qwt_plot_tradingcurve.h \
        $$QWT_SRC_DIR/qwt_plot_layout.h \
        $$QWT_SRC_DIR/qwt_plot_marker.h \
        $$QWT_SRC_DIR/qwt_plot_zoneitem.h \
        $$QWT_SRC_DIR/qwt_plot_textlabel.h \
        $$QWT_SRC_DIR/qwt_plot_rasteritem.h \
        $$QWT_SRC_DIR/qwt_plot_spectrogram.h \
        $$QWT_SRC_DIR/qwt_plot_spectrocurve.h \
        $$QWT_SRC_DIR/qwt_plot_scaleitem.h \
        $$QWT_SRC_DIR/qwt_plot_legenditem.h \
        $$QWT_SRC_DIR/qwt_plot_seriesitem.h \
        $$QWT_SRC_DIR/qwt_plot_shapeitem.h \
        $$QWT_SRC_DIR/qwt_plot_vectorfield.h \
        $$QWT_SRC_DIR/qwt_plot_abstract_canvas.h \
        $$QWT_SRC_DIR/qwt_plot_canvas.h \
        $$QWT_SRC_DIR/qwt_plot_panner.h \
        $$QWT_SRC_DIR/qwt_plot_picker.h \
        $$QWT_SRC_DIR/qwt_plot_zoomer.h \
        $$QWT_SRC_DIR/qwt_plot_magnifier.h \
        $$QWT_SRC_DIR/qwt_plot_rescaler.h \
        $$QWT_SRC_DIR/qwt_point_mapper.h \
        $$QWT_SRC_DIR/qwt_raster_data.h \
        $$QWT_SRC_DIR/qwt_matrix_raster_data.h \
        $$QWT_SRC_DIR/qwt_vectorfield_symbol.h \
        $$QWT_SRC_DIR/qwt_sampling_thread.h \
        $$QWT_SRC_DIR/qwt_samples.h \
        $$QWT_SRC_DIR/qwt_series_data.h \
        $$QWT_SRC_DIR/qwt_series_store.h \
        $$QWT_SRC_DIR/qwt_point_data.h \
        $$QWT_SRC_DIR/qwt_scale_widget.h

    SOURCES += \
        $$QWT_SRC_DIR/qwt_curve_fitter.cpp \
        $$QWT_SRC_DIR/qwt_spline_curve_fitter.cpp \
        $$QWT_SRC_DIR/qwt_weeding_curve_fitter.cpp \
        $$QWT_SRC_DIR/qwt_abstract_legend.cpp \
        $$QWT_SRC_DIR/qwt_legend.cpp \
        $$QWT_SRC_DIR/qwt_legend_data.cpp \
        $$QWT_SRC_DIR/qwt_legend_label.cpp \
        $$QWT_SRC_DIR/qwt_plot.cpp \
        $$QWT_SRC_DIR/qwt_plot_renderer.cpp \
        $$QWT_SRC_DIR/qwt_plot_xml.cpp \
        $$QWT_SRC_DIR/qwt_plot_axis.cpp \
        $$QWT_SRC_DIR/qwt_plot_curve.cpp \
        $$QWT_SRC_DIR/qwt_plot_dict.cpp \
        $$QWT_SRC_DIR/qwt_plot_directpainter.cpp \
        $$QWT_SRC_DIR/qwt_plot_graphicitem.cpp \
        $$QWT_SRC_DIR/qwt_plot_grid.cpp \
        $$QWT_SRC_DIR/qwt_plot_histogram.cpp \
        $$QWT_SRC_DIR/qwt_plot_item.cpp \
        $$QWT_SRC_DIR/qwt_plot_abstract_barchart.cpp \
        $$QWT_SRC_DIR/qwt_plot_barchart.cpp \
        $$QWT_SRC_DIR/qwt_plot_multi_barchart.cpp \
        $$QWT_SRC_DIR/qwt_plot_intervalcurve.cpp \
        $$QWT_SRC_DIR/qwt_plot_zoneitem.cpp \
        $$QWT_SRC_DIR/qwt_plot_tradingcurve.cpp \
        $$QWT_SRC_DIR/qwt_plot_spectrogram.cpp \
        $$QWT_SRC_DIR/qwt_plot_spectrocurve.cpp \
        $$QWT_SRC_DIR/qwt_plot_scaleitem.cpp \
        $$QWT_SRC_DIR/qwt_plot_legenditem.cpp \
        $$QWT_SRC_DIR/qwt_plot_seriesitem.cpp \
        $$QWT_SRC_DIR/qwt_plot_shapeitem.cpp \
        $$QWT_SRC_DIR/qwt_plot_vectorfield.cpp \
        $$QWT_SRC_DIR/qwt_plot_marker.cpp \
        $$QWT_SRC_DIR/qwt_plot_textlabel.cpp \
        $$QWT_SRC_DIR/qwt_plot_layout.cpp \
        $$QWT_SRC_DIR/qwt_plot_abstract_canvas.cpp \
        $$QWT_SRC_DIR/qwt_plot_canvas.cpp \
        $$QWT_SRC_DIR/qwt_plot_panner.cpp \
        $$QWT_SRC_DIR/qwt_plot_rasteritem.cpp \
        $$QWT_SRC_DIR/qwt_plot_picker.cpp \
        $$QWT_SRC_DIR/qwt_plot_zoomer.cpp \
        $$QWT_SRC_DIR/qwt_plot_magnifier.cpp \
        $$QWT_SRC_DIR/qwt_plot_rescaler.cpp \
        $$QWT_SRC_DIR/qwt_point_mapper.cpp \
        $$QWT_SRC_DIR/qwt_raster_data.cpp \
        $$QWT_SRC_DIR/qwt_matrix_raster_data.cpp \
        $$QWT_SRC_DIR/qwt_vectorfield_symbol.cpp \
        $$QWT_SRC_DIR/qwt_sampling_thread.cpp \
        $$QWT_SRC_DIR/qwt_series_data.cpp \
        $$QWT_SRC_DIR/qwt_point_data.cpp \
        $$QWT_SRC_DIR/qwt_scale_widget.cpp

    contains(QWT_CONFIG, QwtOpenGL) {

        lessThan(QT_MAJOR_VERSION, 6) {

            HEADERS += \
                $$QWT_SRC_DIR/qwt_plot_glcanvas.h

            SOURCES += \
                $$QWT_SRC_DIR/qwt_plot_glcanvas.cpp
        }

        greaterThan(QT_MAJOR_VERSION, 4) {

            lessThan( QT_MAJOR_VERSION, 6) {

                greaterThan(QT_MINOR_VERSION, 3) {

                    HEADERS += $$QWT_SRC_DIR/qwt_plot_opengl_canvas.h
                    SOURCES += $$QWT_SRC_DIR/qwt_plot_opengl_canvas.cpp
                }
            }
            else {
                QT += openglwidgets

                HEADERS += $$QWT_SRC_DIR/qwt_plot_opengl_canvas.h
                SOURCES += $$QWT_SRC_DIR/qwt_plot_opengl_canvas.cpp
            }

        }

    }

    contains(QWT_CONFIG, QwtSvg) {

        HEADERS += \
            $$QWT_SRC_DIR/qwt_plot_svgitem.h

        SOURCES += \
            $$QWT_SRC_DIR/qwt_plot_svgitem.cpp
    }

    contains(QWT_CONFIG, QwtPolar) {

        HEADERS += \
            $$QWT_SRC_DIR/qwt_polar.h \
            $$QWT_SRC_DIR/qwt_polar_canvas.h \
            $$QWT_SRC_DIR/qwt_polar_curve.h \
            $$QWT_SRC_DIR/qwt_polar_fitter.h \
            $$QWT_SRC_DIR/qwt_polar_grid.h \
            $$QWT_SRC_DIR/qwt_polar_itemdict.h \
            $$QWT_SRC_DIR/qwt_polar_item.h \
            $$QWT_SRC_DIR/qwt_polar_layout.h \
            $$QWT_SRC_DIR/qwt_polar_magnifier.h \
            $$QWT_SRC_DIR/qwt_polar_marker.h \
            $$QWT_SRC_DIR/qwt_polar_panner.h \
            $$QWT_SRC_DIR/qwt_polar_picker.h \
            $$QWT_SRC_DIR/qwt_polar_plot.h \
            $$QWT_SRC_DIR/qwt_polar_renderer.h \
            $$QWT_SRC_DIR/qwt_polar_spectrogram.h

        SOURCES += \
            $$QWT_SRC_DIR/qwt_polar_canvas.cpp \
            $$QWT_SRC_DIR/qwt_polar_curve.cpp \
            $$QWT_SRC_DIR/qwt_polar_fitter.cpp \
            $$QWT_SRC_DIR/qwt_polar_grid.cpp \
            $$QWT_SRC_DIR/qwt_polar_item.cpp \
            $$QWT_SRC_DIR/qwt_polar_itemdict.cpp \
            $$QWT_SRC_DIR/qwt_polar_layout.cpp \
            $$QWT_SRC_DIR/qwt_polar_magnifier.cpp \
            $$QWT_SRC_DIR/qwt_polar_marker.cpp \
            $$QWT_SRC_DIR/qwt_polar_panner.cpp \
            $$QWT_SRC_DIR/qwt_polar_picker.cpp \
            $$QWT_SRC_DIR/qwt_polar_plot.cpp \
            $$QWT_SRC_DIR/qwt_polar_renderer.cpp \
            $$QWT_SRC_DIR/qwt_polar_spectrogram.cpp
    }
}

greaterThan(QT_MAJOR_VERSION, 4) {

    QT += printsupport
    QT += concurrent
}

contains(QWT_CONFIG, QwtSvg) {

    greaterThan(QT_MAJOR_VERSION, 4) {

        qtHaveModule(svg) {
            QT += svg
        }
        else {
            warning("QwtSvg is enabled in qwtconfig.pri, but Qt has not been built with svg support")
        }
    }
    else {
        QT += svg
    }
}
else {

    DEFINES += QWT_NO_SVG
}

contains(QWT_CONFIG, QwtOpenGL) {

   greaterThan(QT_MAJOR_VERSION, 4) {

        qtHaveModule(opengl) {
            QT += opengl
        }
        else {
            warning("QwtOpenGL is enabled in qwtconfig.pri, but Qt has not been built with opengl support")
        }
    }
    else {
        QT += opengl
    }

    QT += opengl
}
else {

    DEFINES += QWT_NO_OPENGL
}

contains(QWT_CONFIG, QwtWidgets) {

    HEADERS += \
        $$QWT_SRC_DIR/qwt_abstract_slider.h \
        $$QWT_SRC_DIR/qwt_abstract_scale.h \
        $$QWT_SRC_DIR/qwt_arrow_button.h \
        $$QWT_SRC_DIR/qwt_analog_clock.h \
        $$QWT_SRC_DIR/qwt_compass.h \
        $$QWT_SRC_DIR/qwt_compass_rose.h \
        $$QWT_SRC_DIR/qwt_counter.h \
        $$QWT_SRC_DIR/qwt_dial.h \
        $$QWT_SRC_DIR/qwt_dial_needle.h \
        $$QWT_SRC_DIR/qwt_knob.h \
        $$QWT_SRC_DIR/qwt_slider.h \
        $$QWT_SRC_DIR/qwt_thermo.h \
        $$QWT_SRC_DIR/qwt_wheel.h

    SOURCES += \
        $$QWT_SRC_DIR/qwt_abstract_slider.cpp \
        $$QWT_SRC_DIR/qwt_abstract_scale.cpp \
        $$QWT_SRC_DIR/qwt_arrow_button.cpp \
        $$QWT_SRC_DIR/qwt_analog_clock.cpp \
        $$QWT_SRC_DIR/qwt_compass.cpp \
        $$QWT_SRC_DIR/qwt_compass_rose.cpp \
        $$QWT_SRC_DIR/qwt_counter.cpp \
        $$QWT_SRC_DIR/qwt_dial.cpp \
        $$QWT_SRC_DIR/qwt_dial_needle.cpp \
        $$QWT_SRC_DIR/qwt_knob.cpp \
        $$QWT_SRC_DIR/qwt_slider.cpp \
        $$QWT_SRC_DIR/qwt_thermo.cpp \
        $$QWT_SRC_DIR/qwt_wheel.cpp
}
