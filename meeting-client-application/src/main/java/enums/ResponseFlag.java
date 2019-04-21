package enums;

public enum ResponseFlag {
    LOGGING, // pomyślne logowanie
    REGISTR, // pomyślna rejestracja

    USERGRP, // grupy użytkownika
    SHOWGRP, // konkretna grupa
    MAKEGRP, // pomyślne stworzenie grupy
    RMGROUP, // pomyślne usunięcie grupy
    LEAVGRP, // pomyślne wyjście z grupy
    LEADREQ, // zaaplikowano o status lidera
    LEADRSP, // decyzja o nadaniu statusu lidera

    USERREQ, // requesty użytkowników
    USERDEC, // potwierdzenie decyzji

    GRPEVNT, // eventy grupy
    SHOWEVT, // konkretny event
    MAKEEVT, // pomyślne stworzenie eventu
    RMEVENT, // pomyślne usunięcie eventu

    EVNTAPT, // terminy eventu
    SHOWAPT, // konkretny termin
    MAKEAPT, // pomyślne stworzenie nowego terminu
    PROPAPT, // potwierdzenie wysłania propozycji
    RMAPTMT, // pomyślne usunięcie terminu
    APTMDEC, // potwierdzenie decyzji

    NEWVOTE, // pomyślnie zagłosowano
    COMMENT, // pomyślnie dodano komentarz


    __ERROR  // błąd
}
