file(GLOB gumbo_SRC
        "*.h"
        "*.c"
        "*.rl"
        )

add_library(gumbo-parser ${gumbo_SRC})
