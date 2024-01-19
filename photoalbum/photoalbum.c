/*Zachary Meyers
  UID 120279096 */

#include "photoalbum.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Photo *create_photo(int id, const char * description) {
    Photo *new_photo = malloc(sizeof(Photo));
    if(new_photo == NULL) {
        return NULL;
    }
    new_photo->id = id;
    if(description != NULL) {
        new_photo->description = malloc(sizeof(char) * (strlen(description) + 1));
        if(new_photo->description == NULL) {
            return NULL;
        }
        strcpy(new_photo->description, description);
    }
    else {
        new_photo->description = NULL;
    }
    return new_photo;
}
void print_photo(Photo * photo) {
    if(photo != NULL) {
        if(photo->description != NULL) {
            printf("Photo Id: %d, Description: %s\n", photo->id, photo->description);
        }
        else {
            printf("Photo Id: %d, Description: NONE\n", photo->id);
        }
    }
}
void destroy_photo(Photo * photo) {
    if(photo != NULL) {
        free(photo->description);
        free(photo);
    }
}
void initialize_album(Album * album) {
    if(album != NULL) {
        album->size = 0;
    }

}
void print_album(const Album * album) {
    int idx;
    if(album != NULL) {
        if(album->size == 0) {
            printf("Album has no photos.\n");
        }
        else {
            for(idx = 0; idx < album->size; idx++) {
                print_photo(album->all_photos[idx]);
            }
        }
    }
}
void destroy_album(Album * album) {
    int idx;
    if(album != NULL) {
        for(idx = 0; idx < album->size; idx++) {
            destroy_photo(album->all_photos[idx]);
        }
        album->size = 0;
    }
}

void add_photo_to_album(Album * album, int photo_id, const char * description) {
    if(album != NULL && album->size < MAX_ALBUM_SIZE) {
        album->all_photos[album->size++] = create_photo(photo_id, description);
    }

}