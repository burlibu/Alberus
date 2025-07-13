//standards
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
// imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
//src
#include "env.h"
#include "settings.h"

#include "custom_colors.h"

namespace Math {
    /**
 * @brief Funzione che calcola il fattoriale 
 * @param[in] n numero intero per calcolo fattoriale >= 0
 * @return  `res` numero intero risultato del calcolo
 */
    unsigned int fact(unsigned int n);
}

namespace Windows {
    /**
     *  Parameters:
     * 
     * `const ImVec2& cursorpos` posizione del cursore dove sarà l' angolo alto sinistro della schermata
     * `const ImVec2& window_size` larghezza e altezza in un imvec2
     * Attenzione: chiama checkWindowSize se DEBUG è attivo
     */
    void RenderLoginForm(const ImVec2& window_pos, const ImVec2& window_size);

    void showMyWindow(const ImVec2& window_pos, const ImVec2& window_size);
}

/**
 * 
 * 
 * @note 
 *   
 * `const AppSettings settings("App", 800, 600);`
 * 
 * `settings.getWidth();     // ✅ OK (metodo const)`
 * 
 * `settings.setWidth(500); // ❌ ERRORE (oggetto const, metodo non const)`
 */
class AppSettings {
    private:
        std::string appName; // Nascosto, solo la classe può accedere
        int windowWidth; // Nascosto, solo la classe può accedere
        int windowHeigth; // Nascosto, solo la classe può accedere
    public:
    /**
     * @brief Costruttore della classe
     * @param name Nome dell'applicazione
     * @param width Larghezza finestra
     * @param height Altezza finestra
     */
    AppSettings(const std::string& name, int width, int height);
    
    /**
     * @brief Imposta le dimensioni della finestra
     * @param width Larghezza
     * @param height Altezza
     */
    void setWindowSize(int width, int height);
    
    /**
     * @brief Ottiene la larghezza della finestra
     * @return Larghezza corrente
     */
    int getWidth() const; // quando const è scritto dopo il metodo significa che questo metodo non modifica l' oggetto
};

enum class NotificationType {
    INFO,    ///< Notifica informativa
    WARNING, ///< Notifica di avvertimento
    ERROR,   ///< Notifica di errore
    SUCCESS  ///< Notifica di successo
};

/**
 * @brief struct Notifiche
 *
 * `std::string title;` Titolo
 * 
 *  `std::string text;` text inside
 * 
 *  `float duration;` duration
 * 
 *  `std::chrono::steady_clock::time_point start_time;` duration time displays
 */
struct Notification;
/**
 * @brief Function to create a personalized style
 * 
 */
void style();
/*! @brief Mostra una notifica temporanea nell'interfaccia.
 * 
 *  Questa funzione crea una notifica che apparirà nell'interfaccia per un tempo
 *  specificato. La notifica verrà automaticamente rimossa dopo la scadenza del
 *  tempo impostato.
 *
 *  Le notifiche vengono visualizzate nell'angolo in basso a destra dello schermo
 *  e possono essere utilizzate per informare l'utente su eventi, errori o
 *  conferme di azioni.
 *
 *  @param[in] title Il titolo della notifica, visualizzato in grassetto.
 *  @param[in] text Il testo del messaggio della notifica.
 *  @param[in] duration_ms La durata di visualizzazione in millisecondi.
 *
 *  @errors Nessun errore specifico, ma se la memoria è insufficiente la notifica
 *  potrebbe non essere creata.
 *
 *  @thread_safety Questa funzione può essere chiamata da qualsiasi thread.
 *
 *  @sa RenderNotifications
 *  @sa Notification
 *
 *  @since Versione 1.0
 *
 *  @ingroup notifications
 */
void showNotification(); //MEMO6

/**
 * @brief Funzione che prende una stringa colore come bde0fe o bde0fe80 e ritorna un ImVec4 corrispettivo 
 * @param[in] n numero intero per calcolo fattoriale >= 0
 * @return  `res` numero intero risultato del calcolo
 * @note Supporta stringhe da 6 o 8 caratteri
 */
ImVec4 hexToImVec4(const std::string& hex);
/**
 * @brief Funzione che disegna un rettangolo che si illumina
 */
void DrawGlowingRectangle();

/*! @brief Esegue un carico di lavoro intensivo simulato.
 *
 *  @details Questa funzione simula un'operazione computazionalmente pesante
 *  che richiede un tempo significativo per essere completata. È progettata
 *  per testare la gestione di operazioni asincrone e la reattività dell'interfaccia
 *  utente durante l'esecuzione di task lunghi.
 *
 *  @note La funzione attualmente simula un lavoro di 5 secondi tramite
 *  \c std::this_thread::sleep_for. In un'implementazione reale, questo
 *  dovrebbe essere sostituito con calcoli effettivi.
 *
 *  @warning Questa funzione blocca il thread corrente per 5 secondi.
 *  Non chiamare questa funzione dal thread principale dell'interfaccia
 *  grafica senza utilizzare thread separati.
 *
 *  @attention Per un uso corretto, considera l'implementazione di thread
 *  separati per evitare il blocco dell'interfaccia utente.
 *
 *  @remark La funzione è progettata per essere utilizzata come esempio
 *  di gestione di operazioni asincrone in applicazioni ImGui.
 *
 *  @pre Il sistema deve essere inizializzato correttamente.
 *  @post Nessun effetto collaterale permanente.
 *
 *  @invariant La funzione mantiene la coerenza del sistema.
 *
 *  @complexity O(1) - tempo costante di 5 secondi.
 *
 *  @deprecated Questa funzione è deprecata. Usa \c lavoro_lungo() invece.
 *
 *  @see lavoro_lungo
 *  @see esempio_future
 *  @see std::thread
 *  @see std::chrono::sleep_for
 *
 *  @par Esempio di utilizzo:
 *  @code
 *  // Creazione di un thread separato per evitare il blocco dell'UI
 *  std::thread worker(hardLoad);
 *  worker.detach();
 *  @endcode
 *
 *  @par Implementazione attuale:
 *  @code
 *  void hardLoad() {
 *      std::this_thread::sleep_for(std::chrono::seconds(5));
 *  }
 *  @endcode
 *
 *  @bug Nessun bug noto.
 *  @todo Implementare un sistema di progress tracking.
 *  @todo Aggiungere supporto per cancellazione dell'operazione.
 *
 *  @exception Non lancia eccezioni.
 *  @throws Nessuna eccezione.
 *
 *  @return void
 *  @retval Nessun valore di ritorno.
 *
 *  @since Versione 1.0
 *  @version 1.0
 *  @author Alberus
 *  @date 2024
 *  @copyright Tutti i diritti riservati.
 *
 *  @ingroup thread_operations
 *  @defgroup thread_operations Operazioni con Thread
 *  @{
 *  Funzioni per la gestione di operazioni asincrone e thread.
 *  @}
 *
 *  @anchor hardLoad_example
 *  @ref hardLoad_example "Vedi esempio completo"
 *
 *  @relatesalso lavoro_lungo
 *  @relatesalso esempio_future
 *
 *  @hideinitializer
 *  @hidecallgraph
 *  @hidecallergraph
 *
 *  @implements ThreadOperation
 *  @extends BaseOperation
 *  @implements AsyncOperation
 *
 *  @par Performance:
 *  - Tempo di esecuzione: 5 secondi
 *  - Utilizzo memoria: Costante
 *  - Utilizzo CPU: Minimo (sleep)
 *
 *  @par Sicurezza:
 *  - Thread-safe: Sì
 *  - Reentrant: Sì
 *  - Exception-safe: Sì
 *
 *  @par Compatibilità:
 *  - C++11 o superiore
 *  - Windows/Linux/macOS
 *  - Compilatori: GCC, Clang, MSVC
 *
 *  @par Note di implementazione:
 *  La funzione utilizza \c std::this_thread::sleep_for per simulare
 *  un lavoro intensivo. In un'implementazione reale, questo dovrebbe
 *  essere sostituito con calcoli effettivi o operazioni I/O.
 *
 *  @par Best practices:
 *  - Utilizzare sempre thread separati
 *  - Implementare un sistema di feedback per l'utente
 *  - Considerare l'utilizzo di \c std::future per risultati
 *
 *  @par Esempi avanzati:
 *  @code
 *  // Con progress tracking
 *  std::atomic<int> progress{0};
 *  std::thread worker([&progress]() {
 *      for(int i = 0; i < 100; ++i) {
 *          std::this_thread::sleep_for(std::chrono::milliseconds(50));
 *          progress = i;
 *      }
 *  });
 *  @endcode
 */
void HardLoad();

int lavoro_lungo();

void esempio_future();
/**
 * Prende un ImVec2 e lo trasforma in una stringa per esempio (200, 300) diventa "200, 300" 
 */
std::string ImVec2_to_string(const ImVec2& vector );

bool checkWindowSizeChange(const ImVec2& currentSize, float checkIntervalSeconds = 5.0f);


