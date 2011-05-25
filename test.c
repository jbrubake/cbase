#include <stdio.h>

#include "cbase/cbase.h"
#include "cbase/except.h"

void
thrower ()
{
    THROW (X_FOPEN);
}

int
main (int argc, char **argv)
{
    /* Must call this before using kazlib exception handling */
    /* XXX: Should this be a macro that sets except_unhandled_catcher()?
     * */
    if (except_init () == false)
    {
        /* Must call this before exiting */
        except_deinit ();
        return 1;
    }

    TRY
    {
        TRY
        {
            thrower ();
        }
        CATCH
        {
            case X_ALLOC:
                printf ("%s\n", "Caught X_ALLOC");
                break;
            default:
                RETHROW();
        }
        END_CATCH;
    }
    CATCH
    {
        default:
            printf ("%s\n", "Outer try/catch");
    }
    END_CATCH;

    /* Must call this before exiting */
    except_deinit ();

    return 0;
}
