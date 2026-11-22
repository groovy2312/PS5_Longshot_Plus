# PS5 Longshot Plus (`PPSA99198`) — Guía Oficial en Español

**Port Nativo para PlayStation 5 y Builder Multiplataforma (Windows y Linux) — `v0.3.1-plus`**

> 🌐 **Idioma / Language:** [English (`README.md`)](README.md) · **Español (`README_ES.md`)**

---

## Agradecimientos y Créditos

Antes que nada, nuestro más sincero agradecimiento a:

* **[MagicBeanDev](https://magicbean.dev):** Por crear el motor base de recompilación estática *Longshot*, su renderizador Vulkan y sus continuas optimizaciones de rendimiento y estabilidad.
* **[HeydeMoura](https://github.com):** Por la arquitectura inicial del port nativo a PlayStation 5 (`PS5_Vulkan` / `RADV`) y el desarrollo del *Builder* multiplataforma para Windows y Linux.
* **La comunidad de testers y colaboradores:** Por probar cada compilación en consolas reales (PS5 Fat, Slim y Pro), compartir registros de telemetría (`crash_trace.txt`) y aportar sugerencias clave para pulir el proyecto día a día.

---

## Recomendaciones Críticas de Compilación e Instalación (`v0.3.1-plus`)

### 1. En tu PC (Windows / Linux): Recompilar desde cero es ALTAMENTE RECOMENDADO (obligatorio para aplicar los cambios del núcleo)
* Aunque el Builder permite actualizar compilaciones previas, para **`v0.3.1-plus`** es **altamente recomendado (prácticamente obligatorio) generar la carpeta `PPSA99198` completamente desde cero**.
* **Por qué:** Esta versión actualiza el binario principal (`eboot.bin` / `image.bin`), incorpora el nuevo escáner automático de ROMs por *Title ID* en `/data/longshotplus/roms/`, añade el *watchdog* de telemetría de cómputo (`is_compute`) y aplica las correcciones atómicas de RDNA 2 (`#2088`).
* **Cómo hacerlo:** Antes de pulsar **Build**, elimina o elige una carpeta de salida nueva para que no reutilice archivos intermedios viejos de `longshot-ps5-work`.

### 2. En tu PS5: ¿Es obligatorio borrar la instalación anterior?
* **No es estrictamente obligatorio** borrar toda la carpeta anterior (sobrescribir los archivos funciona), **pero SÍ es altamente recomendado** realizar una instalación limpia eliminando las cachés viejas de shaders (`cache/` y `radv-shader-cache/`) de versiones anteriores.
* **Por qué:** Evita arrastrar *pipelines* compilados con versiones previas o configuraciones residuales que puedan provocar comportamientos inconsistentes.

---

## Cómo Respaldar tus Partidas Guardadas (`user/`) Antes de Actualizar

Todo tu progreso, perfiles, capturas de guardado y ajustes del juego se almacenan dentro de la subcarpeta **`user/`** en tu PS5. **Nunca borres `/data/homebrew/PPSA99198` sin respaldar esta carpeta primero.**

### Paso a paso por FTP (FileZilla / WinSCP / Cyberduck)
1. Conéctate a tu PS5 por FTP (puerto `2121`).
2. Navega hasta:
   `/data/homebrew/PPSA99198/`
3. Descarga a tu PC una copia de seguridad de:
   * **`user/`** *(Carpeta completa: contiene `slot_00/`, `progress.sav`, `caption.sav`, `account.sav` y `option.sav`)*
   * **`longshot_options.ini`** *(Opcional: conserva tus ajustes de gráficos, audio y controles)*
   * **`fsr4/lite/`** *(Opcional: si instalaste los pesos INT8 de AMD FSR 4.1.2)*
4. Ahora ya puedes eliminar la carpeta antigua `/data/homebrew/PPSA99198/` en la PS5 y subir la nueva carpeta **`PPSA99198`** recién compilada.
5. Una vez copiada la nueva versión, vuelve a subir tu respaldo de **`user/`** (y `longshot_options.ini` / `fsr4/lite/` si los guardaste) dentro de `/data/homebrew/PPSA99198/`, sobrescribiendo si te lo solicita.

---

## Detección Automática del Archivo `.nup` y Estructura de Carpetas en PS5

En **`v0.3.1-plus`**, el juego ya **no depende de un único nombre de archivo fijo**: al arrancar, escanea automáticamente las carpetas compatibles en orden de prioridad y lee la cabecera de cada archivo `.nup` hasta verificar el *Title ID* oficial de *Ocarina of Time* (`0400486024DEC000`).

### Orden de búsqueda automática en la PS5
1. **`/data/longshotplus/roms/`** *(Ruta principal recomendada — acepta cualquier nombre terminado en `.nup`, por ejemplo `oot.nup` o `zelda_oot.nup`)*
2. **`/data/longshot/roms/`** *(Respaldo automático)*
3. **`/data/eglantineps5/roms/`** *(Respaldo automático)*
4. **`/data/lichii/roms/oot/`** *(Respaldo automático)*

### Diagrama de cómo quedan ordenadas las carpetas en tu PS5

```text
/data/
├── homebrew/
│   └── PPSA99198/                     <-- Carpeta generada por PS5 Longshot Plus Builder
│       ├── eboot.bin                  <-- Ejecutable principal recompilado
│       ├── image.bin                  <-- Código AArch64 traducido del juego
│       ├── longshot_env.txt           <-- Parámetros de memoria y rendimiento (PS5 Fat / Pro)
│       ├── longshot_options.ini       <-- Configuración del menú interno (se crea al guardar ajustes)
│       ├── user/                      <-- ★ TUS PARTIDAS GUARDADAS (¡RESPALDAR SIEMPRE!)
│       │   └── slot_00/
│       │       ├── progress.sav
│       │       └── caption.sav
│       ├── fsr4/
│       │   └── lite/                  <-- (Opcional) Pesos INT8 de AMD FSR 4.1.2 Lite
│       ├── cache/                     <-- Caché de programas de shader (se regenera sola)
│       ├── radv-shader-cache/         <-- Caché de pipelines Vulkan RADV (se regenera sola)
│       └── logs/
│           └── crash_trace.txt        <-- Registro en tiempo real de watchdog y memoria
│
└── longshotplus/
    └── roms/
        └── oot.nup                    <-- ★ Tu volcado .nup (Title ID 0400486024DEC000, v131072)
```

---

## Avisos Importantes de Jugabilidad y Áreas Conocidas

* **⚠️ Coliseo de los Monstruos (*Monster Coliseum*):** **De momento NO se recomienda visitar el Coliseo de los Monstruos.** En esa sala específica existe un *compute shader* (`prog_key=53fcaee4dc45c6ee`) que provoca congelamientos constantes en la GPU RDNA 2 de la PS5 tras ~30 segundos. Ya lo tenemos localizado en los registros y trabajaremos en su corrección para próximas actualizaciones.
* **Áreas verificadas y estables en PS5 Fat (12 GB):** Bosque Kokiri, Pradera de Hyrule, Rancho Lon Lon, Aldea Kakariko, Dominio de los Zora, Valle Gerudo y Templo del Bosque.
* **Consejo para sesiones largas en PS5 Fat / Slim:** Guarda manualmente antes de cruzar entre muchas zonas abiertas seguidas. Si el sistema detecta que la memoria libre baja del umbral de seguridad (`220 MiB`), cerrará el juego limpiamente (`MEMORY_FLOOR_EXIT`) para proteger tus partidas y evitar el error de sistema `CE-108255-1`; basta con volver a abrir **LONGSHOT PLUS** desde el menú de la PS5 para continuar.

---

## Resumen de Novedades Técnicas en `v0.3.1-plus`

* **Corrección de cuelgues atómicos de cómputo RDNA 2 / RADV (`#2088`):** Serializa los bucles atómicos de punto flotante por subgrupo mediante `OpGroupNonUniformElect` (`SubgroupCasLoop`), eliminando cuelgues de GPU de 2 segundos en pases de iluminación de templos.
* **Escáner dedicado de ROMs (`/data/longshotplus/roms/`) y validación de Title ID (`ps5_is_oot_nup`):** Detecta automáticamente cualquier `.nup` válido (`0400486024DEC000`) en `/data/longshotplus/roms/` o rutas alternativas.
* **Salida directa FSR 3.1 (`#2085`) y salto hacia atrás a alto FPS (`#2071`):** Ahorra ~1 ms por fotograma en FSR 3.1 y corrige la altura del *backflip* por encima de 60 FPS (`HOS_FPS_TAKEOFF`).
* **Gestión de memoria en 4 niveles para PS5 Fat:** `zone_boost` proactivo (`< 2420 MiB`), bloqueo de re-expansión ASTC, purga de *render targets* obsoletos (`1152 / 512 MiB`) y piso preventivo `MEMORY_FLOOR_EXIT` (`220 MiB`) con `RX_VK_TEX_MAX_DIM=256` y `RX_VK_TEX_SKIP_MB=1` (~1.88 GiB libres verificados).
* **Telemetría ampliada en `crash_trace.txt`:** Registra `is_compute=1|0`, `prog_key`, `free_mem` y `zone_boost` en tiempo real sin búfer (`O_SYNC`).
* **Mejoras del Builder (`#59`, `#62`, `#63`):** Incluye `PS5LongshotPlusBuilder-cli.cmd` redirigible en Windows, modo de bajo consumo de memoria (`2–3 GB` de RAM) y corrección del paso 6 en PyQt6.
