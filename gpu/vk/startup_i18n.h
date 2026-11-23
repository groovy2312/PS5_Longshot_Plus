#pragma once
#include <cstdio>
#include <string>

namespace mkwvk::startup_i18n {

inline std::string translate(const std::string& in, const char* lang_code) {
    if (in.empty()) return in;
    const std::string lang = lang_code ? lang_code : "";
    auto is_es = [&]() { return lang.rfind("es", 0) == 0; };
    auto is_pt = [&]() { return lang.rfind("pt", 0) == 0; };
    auto is_fr = [&]() { return lang.rfind("fr", 0) == 0; };
    auto is_de = [&]() { return lang.rfind("de", 0) == 0; };
    auto is_it = [&]() { return lang.rfind("it", 0) == 0; };
    auto is_ja = [&]() { return lang.rfind("ja", 0) == 0; };
    auto is_ko = [&]() { return lang.rfind("ko", 0) == 0; };
    auto is_zh = [&]() { return lang.rfind("zh", 0) == 0; };

    if (in == "STEP 1 OF 2") {
        if (is_es() || is_pt()) return "Paso 1 de 2";
        if (is_fr()) return "Étape 1 sur 2";
        if (is_de()) return "Schritt 1 von 2";
        if (is_it()) return "Passaggio 1 di 2";
        if (is_ja()) return "ステップ 1 / 2";
        if (is_ko()) return "1 / 2 단계";
        if (is_zh()) return "第 1 步（共 2 步）";
        return "Step 1 of 2";
    }
    if (in == "STEP 2 OF 2") {
        if (is_es() || is_pt()) return "Paso 2 de 2";
        if (is_fr()) return "Étape 2 sur 2";
        if (is_de()) return "Schritt 2 von 2";
        if (is_it()) return "Passaggio 2 di 2";
        if (is_ja()) return "ステップ 2 / 2";
        if (is_ko()) return "2 / 2 단계";
        if (is_zh()) return "第 2 步（共 2 步）";
        return "Step 2 of 2";
    }
    if (in == "Getting the game ready for your console") {
        if (is_es()) return "Preparando el juego para tu consola";
        if (is_pt()) return "Preparando o jogo para o seu console";
        if (is_fr()) return "Préparation du jeu pour votre console";
        if (is_de()) return "Spiel wird für deine Konsole vorbereitet";
        if (is_it()) return "Preparazione del gioco per la tua console";
        if (is_ja()) return "コンソール用にゲームを準備しています";
        if (is_ko()) return "콘솔용 게임을 준비하는 중";
        if (is_zh()) return "正在为您的主机准备游戏";
        return in;
    }
    if (in == "Getting the game ready") {
        if (is_es()) return "Preparando el juego";
        if (is_pt()) return "Preparando o jogo";
        if (is_fr()) return "Préparation du jeu";
        if (is_de()) return "Spiel wird vorbereitet";
        if (is_it()) return "Preparazione del gioco";
        if (is_ja()) return "ゲームを準備しています";
        if (is_ko()) return "게임 준비 중";
        if (is_zh()) return "正在准备游戏";
        return in;
    }
    if (in == "Preparing shaders") {
        if (is_es() || is_pt()) return "Preparando shaders";
        if (is_fr()) return "Préparation des shaders";
        if (is_de()) return "Shader werden vorbereitet";
        if (is_it()) return "Preparazione degli shader";
        return in;
    }
    if (in == "Building pipelines") {
        if (is_es() || is_pt()) return "Compilando pipelines";
        if (is_fr()) return "Compilation des pipelines";
        if (is_de()) return "Pipelines werden erstellt";
        if (is_it()) return "Creazione delle pipeline";
        return in;
    }
    if (in == "Loading pipelines") {
        if (is_es()) return "Cargando pipelines";
        if (is_pt()) return "Carregando pipelines";
        if (is_fr()) return "Chargement des pipelines";
        if (is_de()) return "Pipelines werden geladen";
        if (is_it()) return "Caricamento delle pipeline";
        return in;
    }
    if (in == "Starting the game") {
        if (is_es()) return "Iniciando el juego";
        if (is_pt()) return "Iniciando o jogo";
        if (is_fr()) return "Démarrage du jeu";
        if (is_de()) return "Spiel wird gestartet";
        if (is_it()) return "Avvio del gioco";
        return in;
    }
    if (in == "Closing") {
        if (is_es()) return "Cerrando";
        if (is_pt()) return "Fechando";
        if (is_fr()) return "Fermeture";
        if (is_de()) return "Wird geschlossen";
        if (is_it()) return "Chiusura";
        return in;
    }
    if (in == "What is ready is kept for the next start" || in == "Keeping what is prepared for the next start") {
        if (is_es()) return "Lo que ya está listo se guarda para el próximo inicio";
        if (is_pt()) return "O que já está pronto fica salvo para a próxima inicialização";
        if (is_fr()) return "Ce qui est prêt est conservé pour le prochain démarrage";
        return in;
    }
    if (in == "Restarting to free memory, then going on") {
        if (is_es()) return "Reiniciando para liberar memoria y continuar";
        if (is_pt()) return "Reiniciando para liberar memória e continuar";
        if (is_fr()) return "Redémarrage pour libérer de la mémoire, puis reprise";
        return in;
    }
    if (in == "Ready! Restarting the game") {
        if (is_es()) return "¡Listo! Reiniciando el juego";
        if (is_pt()) return "Pronto! Reiniciando o jogo";
        if (is_fr()) return "Prêt ! Redémarrage du jeu";
        return in;
    }
    if (in == "Reading the game's shaders") {
        if (is_es()) return "Leyendo los shaders del juego";
        if (is_pt()) return "Lendo os shaders do jogo";
        return in;
    }
    if (in == "Reading the pipeline notes" || in == "Loading the shader cache") {
        if (is_es()) return "Cargando la caché de shaders";
        if (is_pt()) return "Carregando o cache de shaders";
        return in;
    }
    if (in == "a few seconds left") {
        if (is_es()) return "quedan unos segundos";
        if (is_pt()) return "faltam alguns segundos";
        if (is_fr()) return "quelques secondes restantes";
        return in;
    }
    if (in.rfind("about ", 0) == 0) {
        int mins = 0, secs = 0, val = 0;
        char b[64];
        if (sscanf(in.c_str(), "about %d min %d s left", &mins, &secs) == 2) {
            if (is_es()) { snprintf(b, sizeof b, "quedan unos %d min %d s", mins, secs); return b; }
            if (is_pt()) { snprintf(b, sizeof b, "faltam cerca de %d min %d s", mins, secs); return b; }
            if (is_fr()) { snprintf(b, sizeof b, "environ %d min %d s restantes", mins, secs); return b; }
        }
        if (sscanf(in.c_str(), "about %d s left", &val) == 1) {
            if (is_es()) { snprintf(b, sizeof b, "quedan unos %d s", val); return b; }
            if (is_pt()) { snprintf(b, sizeof b, "faltam cerca de %d s", val); return b; }
            if (is_fr()) { snprintf(b, sizeof b, "environ %d s restantes", val); return b; }
        }
        if (sscanf(in.c_str(), "about %d min left", &val) == 1) {
            if (is_es()) { snprintf(b, sizeof b, "quedan unos %d min", val); return b; }
            if (is_pt()) { snprintf(b, sizeof b, "faltam cerca de %d min", val); return b; }
            if (is_fr()) { snprintf(b, sizeof b, "environ %d min restantes", val); return b; }
        }
    }
    if (in.find("preparing the game's graphics") != std::string::npos) {
        if (is_es())
            return "PS5 Longshot Plus está preparando los gráficos del juego. Esto ocurre una sola vez tras instalar o actualizar.\n"
                   "Al hacerlo ahora, el juego no tendrá que detenerse a compilarlos mientras juegas, lo cual consume memoria\n"
                   "y puede cerrarlo en zonas grandes como la Ciudadela de Hyrule. El juego puede reiniciarse unas veces\n"
                   "para liberar memoria y continuará donde se quedó; al terminar, iniciará solo.\n"
                   "Puedes cerrarlo en cualquier momento: lo que ya esté listo se guarda.";
        if (is_pt())
            return "O PS5 Longshot Plus está preparando os gráficos do jogo. Isso acontece uma única vez após instalar ou atualizar.\n"
                   "Feito agora, o jogo não precisa parar para compilá-los enquanto você joga, o que consome memória\n"
                   "e pode fechá-lo em áreas grandes como a Cidade do Castelo. O jogo pode reiniciar algumas vezes\n"
                   "para liberar memória e continuará de onde parou; ao terminar, iniciará sozinho.\n"
                   "Você pode fechar a qualquer momento: o que já estiver pronto fica salvo.";
        if (is_fr())
            return "PS5 Longshot Plus prépare les graphismes du jeu. Cela n'a lieu qu'une fois après une installation ou mise à jour.\n"
                   "Fait maintenant, le jeu n'aura pas à s'arrêter pour les compiler en cours de partie, ce qui utilise de la mémoire\n"
                   "et peut le fermer dans les grandes zones comme la Place du Marché. Le jeu peut redémarrer quelques fois\n"
                   "pour libérer de la mémoire et reprendra là où il s'était arrêté ; une fois terminé, il démarrera tout seul.\n"
                   "Vous pouvez le fermer à tout moment : ce qui est prêt est conservé.";
        std::string en = in;
        if (en.rfind("Longshot ", 0) == 0) en = "PS5 Longshot Plus " + en.substr(9);
        return en;
    }
    return in;
}

} // namespace mkwvk::startup_i18n
