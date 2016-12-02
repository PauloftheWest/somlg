#include "dialog.h"
#include <stdlib.h>
#include <string.h>

somlg_dialog* parseDialog(const char *_str) {
    int i;
    char *str = strdup(_str);
    int len = strlen(str);
    int spos = 0;
    int state = 0;
    int optionNum = 0;
    int pipeCount = 0;
    somlg_dialog *ret = malloc(sizeof(somlg_dialog));

    /* Trim the string.*/
    while (str[len-1] == '\n' || str[len-1] == '\r') {
        str[--len] = '\0';
    }

    /* Get the number of pipes */
    for (i = 0; i < len; i++) {
        if (str[i] == '|' && (i != len - 1)
                          && ((i == len-1 || str[i+1] != '|'))
                          && ((i == 0 || str[i-1] != '|'))) {
            pipeCount++;
        }
    }

    ret->mNumOptions = pipeCount - 1;
    if (ret->mNumOptions > 0) {
        ret->mOptions = malloc(sizeof(char*) * ret->mNumOptions);
    }

    for (i = 0; i < len; i++) {
        if ((str[i] == '|' && str[i-1] != '|') || i == len-1) {

            if (i != len-1 || str[i] == '|') {
                str[i] = '\0';
            }

            switch(state) {
                case 0:
                    ret->mDecoration = atoi(str + spos);
                    state++;
                    break;
                case 1:
                    ret->mMessage = strdup(str + spos);
                    state++;
                    break;
                case 2:
                    ret->mOptions[optionNum++] = strdup(str + spos);
                    break;
            }
            spos = i+1;
        }
    }

    free(str);
    return ret;
}

void freeDialog(somlg_dialog *dialog) {
    int i;

    free(dialog->mMessage);

    for (i = 0; i < dialog->mNumOptions; i++) {
        free(dialog->mOptions[i]);
    }

    if (dialog->mNumOptions > 0) {
        free(dialog->mOptions);
    }

    dialog->mOptions = 0;
}

char *getMessage(const somlg_dialog *dialog) {
    return dialog->mMessage;
}

unsigned int getNumOptions(const somlg_dialog *dialog) {
    return dialog->mNumOptions;
}

char *getOption(const somlg_dialog *dialog, const int index) {
    if (index < 0 || index >= dialog->mNumOptions) {
        return NULL;
    }

    return dialog->mOptions[index];
}

int getDecorationId(const somlg_dialog *dialog) {
    return dialog->mDecoration;
}
