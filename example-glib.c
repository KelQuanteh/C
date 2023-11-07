#include <glib.h>
#include <stdio.h>

void displayLinkedList(GList *list) {
    GList *current = list;

    while (current != NULL) {
        // Assuming the linked list contains strings
        char *data = (char *)current->data;
        printf("%s ", data);

        current = current->next;
    }

    printf("\n");
}

int main() {
    GList *frutas = NULL;
    frutas = g_list_append(frutas, g_strdup("Maçã"));
    frutas = g_list_append(frutas, g_strdup("Banana"));
    frutas = g_list_remove(frutas, "Maçã");

    displayLinkedList(frutas);

    g_list_free_full(frutas, g_free);

    return 0;
}