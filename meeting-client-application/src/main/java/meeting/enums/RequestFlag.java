package meeting.enums;

public enum RequestFlag {
    LOGGING, // logowanie
    SIGNOUT, // wylogowanie - zastanowić się, czy musimy wysyłać requesta, żeby się wylogować
    REGISTR, // rejestracja

    USERGRP, // wyświetl grupy użytkownika
    SHOWGRP, // pokaż konkretną grupę <-----czym sie rozni od: GRPEVNT, // wyświetl eventy grupy
    GRPLIST, // pokaż wszystkie dostepne grupy
    MAKEGRP, // stwórz nową grupę
    RMGROUP, // usuń grupę
    LEAVGRP, // wyjdź z grupy
    LEADREQ, // aplikuj o status lidera
    MEMBREQ, // aplikuj o dolaczenie do grupy

    USERREQ, // wyświetl requesty użytkowników
    USERDEC, // odrzuć użytkownika
    USERACC, // zaakceptuj użytkownika

    GRPEVNT, // wyświetl eventy grupy
    SHOWEVT, // pokaż konkretny event
    MAKEEVT, // stwórz nowy event
    RMEVENT, // usuń event

    EVNTAPT, // pokaż terminy eventu
    SHOWAPT, // wybierz konkretny termin
    MAKEAPT, // stwórz nowy termin
    PROPAPT, // proponuj nowy termin
    RMAPTMT, // usuń termin
    APTMDEC, // zaakceptuj/odrzuć termin

    NEWVOTE, // zagłosuj na termin
    COMMENT  // dodaj komentarz
}
