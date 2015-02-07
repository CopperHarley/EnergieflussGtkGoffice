#include "my-intensitybox.h"

/* 'private'/'protected' functions */
static void my_intensity_box_class_init (MyIntensityBoxClass * klass);
static void my_intensity_box_init (MyIntensityBox * self);
static void my_intensity_box_finalize (GObject *);
static void my_intensity_box_dispose (GObject *);

enum
{
    PROP_0,
    PROP_Y_MAX,
    PROP_Y_MIN,
    PROP_Y,
    N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

struct _MyIntensityBoxPrivate
{
    /* private members go here */
    gint i;

    gdouble y_max, y, y_min;
};

G_DEFINE_TYPE_WITH_PRIVATE (MyIntensityBox, my_intensity_box,
                            GTK_TYPE_DRAWING_AREA);

GQuark
my_intensity_box_error_quark (void)
{
    return g_quark_from_static_string ("my-intensity-box-error-quark");
}

static void
my_intensity_box_set_property (GObject * object,
                               guint property_id,
                               const GValue * value, GParamSpec * pspec)
{
    MyIntensityBox *self = MY_INTENSITY_BOX (object);

    MyIntensityBoxPrivate *priv = my_intensity_box_get_instance_private (self);

    switch (property_id) {

        case PROP_Y_MAX:
            priv->y = g_value_get_double (value);
            break;

        case PROP_Y_MIN:
            priv->y = g_value_get_double (value);
            break;

        case PROP_Y:
            priv->y = g_value_get_double (value);
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
    }
}

static void
my_intensity_box_get_property (GObject * object,
                               guint property_id, GValue * value,
                               GParamSpec * pspec)
{
    MyIntensityBox *self = MY_INTENSITY_BOX (object);

    MyIntensityBoxPrivate *priv = my_intensity_box_get_instance_private (self);

    switch (property_id) {

        case PROP_Y:
            g_value_set_double (value, priv->y);
            break;

        case PROP_Y_MIN:
            g_value_set_double (value, priv->y_max);
            break;

        case PROP_Y_MAX:
            g_value_set_double (value, priv->y_min);
            break;

        default:
            /* We don't have any other property... */
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
    }
}

gboolean
my_intensity_box_draw (GtkWidget * widget, cairo_t * cr)
{
    MyIntensityBox *self = MY_INTENSITY_BOX (widget);

    MyIntensityBoxPrivate *priv = my_intensity_box_get_instance_private (self);

    gint x, y;
    gint width, height;

    gdouble line_width = 2;

    x = 0;
    y = 0;

    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);

    cairo_rectangle (cr, width/4, height, width-width/2, - (priv->y/(priv->y_max-priv->y_min)) * height );
    cairo_set_source_rgba (cr, 1, 0, 0, 0.5);
    cairo_fill (cr);

    cairo_set_line_width (cr, line_width);
    cairo_set_source_rgba (cr, 0, 0, 0, 0.8);
    cairo_move_to (cr, x, height-line_width/2);
    cairo_rel_line_to (cr, width, 0);
    cairo_stroke (cr);

    /*cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 0.8);*/
    /*cairo_move_to (cr, x, height);*/
    /*cairo_rel_line_to (cr, 0, -height);*/
    /*cairo_stroke (cr);*/

    return TRUE;
}

static GtkSizeRequestMode
my_intensity_box_get_request_mode (GtkWidget * widget)
{
    return GTK_SIZE_REQUEST_HEIGHT_FOR_WIDTH;
}

static void
my_intensity_box_get_preferred_width (GtkWidget * widget,
                                      gint * minimum_size, gint * natural_size)
{
    *minimum_size = 20;
    *natural_size = 40;
}

static void
my_intensity_box_get_preferred_height (GtkWidget * widget,
                                       gint * minimum_size, gint * natural_size)
{
    /**minimum_size = 1;*/
    /**natural_size = 1;*/
}

static void
my_intensity_box_get_preferred_width_for_height (GtkWidget * widget,
                                                 gint height,
                                                 gint * minimum_width,
                                                 gint * natural_width)
{
    *minimum_width = 100;
    *natural_width = 100;
}

static void
my_intensity_box_get_preferred_height_for_width (GtkWidget * widget,
                                                 gint width,
                                                 gint * minimum_height,
                                                 gint * natural_height)
{
    *minimum_height = 100;
    *natural_height = 150;
}

static void
my_intensity_box_class_init (MyIntensityBoxClass * klass)
{
    GObjectClass *gobject_class;
    GtkWidgetClass *widget_class;

    gobject_class = G_OBJECT_CLASS (klass);
    widget_class = (GtkWidgetClass *) klass;

    gobject_class->finalize = my_intensity_box_finalize;
    gobject_class->dispose = my_intensity_box_dispose;
    gobject_class->get_property = my_intensity_box_get_property;
    gobject_class->set_property = my_intensity_box_set_property;

    widget_class->draw = my_intensity_box_draw;

    widget_class->get_request_mode = my_intensity_box_get_request_mode;
    widget_class->get_preferred_width = my_intensity_box_get_preferred_width;
    widget_class->get_preferred_height = my_intensity_box_get_preferred_height;
    widget_class->get_preferred_width_for_height =
        my_intensity_box_get_preferred_width_for_height;
    widget_class->get_preferred_height_for_width =
        my_intensity_box_get_preferred_height_for_width;
}

static void
my_intensity_box_init (MyIntensityBox * self)
{
    MyIntensityBoxPrivate *priv;

    priv = my_intensity_box_get_instance_private (self);

    /* to init any of the private data, do e.g: */

    priv->y_min = 0.0;
    priv->y_max = 1.0;
    priv->y = 0.5;
}

static void
my_intensity_box_dispose (GObject * object)
{
    G_OBJECT_CLASS (my_intensity_box_parent_class)->dispose (object);
}

static void
my_intensity_box_finalize (GObject * object)
{
    /* free/unref instance resources here */
    G_OBJECT_CLASS (my_intensity_box_parent_class)->finalize (object);
}

MyIntensityBox *
my_intensity_box_new (void)
{
    MyIntensityBox *self;

    self = g_object_new (MY_TYPE_INTENSITY_BOX, NULL);

    return self;
}
