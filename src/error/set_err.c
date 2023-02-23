#include "error.h"
#include "model.h"

int	set_err(int err)
{
	data()->err = (int)err;
	return (err);
}
