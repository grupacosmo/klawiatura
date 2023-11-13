Projekt kilkuprzyciskowej klawiatury.

Instrukcja:
1. Należy wygerować kopletny kod z użyciem STM32 CubeMX 6.8.1 (ważne jest, by była to dokładnie ta wersja)
File -> load project
2. Następnie trzeba podmienić pliki main.c, usbd_hid.c, usbd_hid.h i usb_desc.c na te pobrane z repozytorium
3. Można skompilować program i wgrać go na płytkę np. za pomocą IAR Embedded Workbech 

Uwaga:
1.Przy podłączniu tact-switchy należy pamiętać o oporniku.
2.Na płytce do obsługi programowej klawiatury służy port USB zlokaliozowany od strony zewnętrznej, a do wgrywania programu - wewnętrznej.