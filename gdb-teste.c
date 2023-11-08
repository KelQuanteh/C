#include <stdio.h>
#include <stdlib.h>
#include <gdbm.h>

int main(void) {
    // Declare variables for the GDBM database, key, and value.
    GDBM_FILE db;
    datum key, value;

    // Open a GDBM database file named "meu_banco.db".
    db = gdbm_open("meu_banco.db", 0, GDBM_WRCREAT, 0666, NULL);

    // Set the key and value for storage.
    key.dptr = "chave";  // Key: "chave"
    key.dsize = sizeof("chave");
    value.dptr = "valor"; // Value: "valor"
    value.dsize = sizeof("valor");

    // Store the key-value pair in the database (or replace if the key already exists).
    gdbm_store(db, key, value, GDBM_REPLACE);

    // Retrieve a value from the database using the key "chave".
    key.dptr = "chave";
    key.dsize = sizeof("chave");
    value = gdbm_fetch(db, key);

    // Print the retrieved value.
    printf("Valor da chave 'chave': %s\n", value.dptr);

    // Close the GDBM database.
    gdbm_close(db);

    // Return a success status.
    return EXIT_SUCCESS;
}
