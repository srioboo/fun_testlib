# Tareas de Mejora: fun_testlib

Seguimiento de implementación de mejoras. Marca las tareas como completadas (`[x]`) conforme se implementen.

---

## 📌 FASE 1: Fundamentos (Essential)

Estas tareas son críticas para habilitar CI/CD y mejorar la usabilidad básica.

### 1.1 Retorno de estado en aserciones
- [ ] Crear struct `fun_test_context_t` para tracking global de resultados
- [X] Modificar `fun_assert_int()` para retornar `int` (1=OK, 0=KO)
- [ ] Incrementar contador interno en cada assert
- [ ] Actualizar header `funtestlib.h` con nueva firma
- [ ] Verificar backward compatibility

**Complejidad**: Baja | **Impacto**: Alto

---

### 1.2 Macro simplificador FUN_TEST()
- [ ] Diseñar macro `FUN_TEST(name, body)` que encapsule setup/teardown
- [ ] Eliminar necesidad de `fun_method_name()` / `fun_free_str()` en macros
- [ ] Implementar context automático en macro
- [ ] Crear ejemplo de uso en header
- [ ] Documentar patrones de uso

**Complejidad**: Media | **Impacto**: Alto

---

### 1.3 Resumen de resultados y exit codes
- [ ] Implementar `fun_tests_summary()` que imprima estadísticas
- [ ] Implementar `fun_tests_get_exit_code()` (retorna 0 si OK, 1 si fallos)
- [ ] Agregar contador de tests totales/pasados/fallidos
- [ ] Formatear salida con colores
- [ ] Permitir reset de contadores con `fun_tests_reset()`

**Complejidad**: Media | **Impacto**: Muy Alto (habilitador de CI/CD)

---

## 📌 FASE 2: Flexibilidad (Important)

Extiende soporte a más tipos de datos y elimina verbosidad.

### 2.1 Aserciones para strings
- [ ] Implementar `fun_assert_str(const char *expected, const char *actual)`
- [ ] Usar `strcmp()` para comparación
- [ ] Manejar casos NULL con seguridad
- [ ] Retornar `int` como otras aserciones
- [ ] Crear macro `FUN_ASSERT_STR(exp, act)` para consistencia

**Complejidad**: Baja | **Impacto**: Medio

---

### 2.2 Aserciones para punteros
- [ ] Implementar `fun_assert_ptr(void *ptr, int should_be_null)`
  - `should_be_null=1`: Espera NULL
  - `should_be_null=0`: Espera non-NULL
- [ ] Retornar `int` como otras aserciones
- [ ] Crear macros `FUN_ASSERT_NOT_NULL()` y `FUN_ASSERT_NULL()`
- [ ] Agregar soporte opcional para comparación de direcciones de punteros

**Complejidad**: Baja | **Impacto**: Medio

---

### 2.3 Eliminar verbosidad de fun_method_name() / fun_free_str()
- [ ] Refactor: las macros deben manejar context internamente
- [ ] Deprecar `fun_method_name()` y `fun_free_str()` (mantener para compatibilidad)
- [ ] Reescribir ejemplos en `src-tests/` sin usar malloc de strings
- [ ] Simplificar patrón de test a solo:
  ```c
  FUN_TEST("name", {
      FUN_ASSERT_INT(expected, actual);
  })
  ```
- [ ] Actualizar README.md con nuevo patrón

**Complejidad**: Alta (refactor) | **Impacto**: Muy Alto (DX improvement)

---

## 📌 FASE 3: Integración (Nice-to-have)

Mejoras para escalabilidad y onboarding.

### 3.1 Script generator de templates
- [ ] Crear script `funtest-init.sh` o ejecutable
- [ ] Generar estructura `src-tests/` automáticamente
- [ ] Crear `Makefile` template para tests
- [ ] Crear `test.h` y `main_test.c` base
- [ ] Agregar `.gitignore` apropiadido
- [ ] Documentar uso del script

**Complejidad**: Baja | **Impacto**: Bajo (UX improvement)

---

### 3.2 Soporte para test groups
- [ ] Implementar macro `FUN_GROUP(name, body)`
- [ ] Agrupar tests relacionados con mejor output
- [ ] Reportar resultados por grupo
- [ ] Mantener contadores separados por grupo (opcional)
- [ ] Crear ejemplo con múltiples grupos

**Complejidad**: Media | **Impacto**: Bajo (organización)

---

### 3.3 Sistema de configuración
- [ ] Crear struct `fun_config_t` para settings globales
- [ ] Implementar `fun_config_set(option, value)`
- [ ] Opción: `FUN_CFG_COLORS` (0=disabled, 1=enabled)
- [ ] Opción: `FUN_CFG_VERBOSE` (0=quiet, 1=verbose)
- [ ] Opción: `FUN_CFG_STOP_ON_FAIL` (0=continue, 1=stop)
- [ ] Documentar opciones disponibles

**Complejidad**: Media | **Impacto**: Bajo (CI/CD integration)

---

## 🐛 Bug Fixes (Inmediatos)

Problemas críticos que se deben arreglar primero:

### Bug: Malloc incorrecto en fun_method_name()
- [ ] Arreglar: `malloc(len * sizeof(char*))` → `malloc(len * sizeof(char))`
- [ ] Revisar si hay otros usos problemáticos de sizeof
- [ ] Ejecutar `make sane` para verificar

**Prioridad**: CRÍTICA | **Riesgo**: Bajo

---

## 📋 Checklist de Validación por Fase

### Después de FASE 1:
- [ ] `make test` pasa sin errores
- [ ] Exit code es 0 si todos tests OK, 1 si alguno falla
- [ ] `fun_tests_summary()` imprime resultados correctos
- [ ] Backward compatibility con código viejo
- [ ] README.md y AGENTS.md actualizados

### Después de FASE 2:
- [ ] `fun_assert_str()` funciona con strings
- [ ] `fun_assert_ptr()` detecta NULL/non-NULL
- [ ] Ejemplos usan macros en lugar de malloc
- [ ] `make sane` y `make val` pasan sin errores
- [ ] Cobertura de tipos: int, str, ptr

### Después de FASE 3:
- [ ] `funtest-init.sh` genera boilerplate correcto
- [ ] `FUN_GROUP()` agrupa tests correctamente
- [ ] Configuración se aplica globalmente
- [ ] Documentación completa

---

## 📝 Notas de Implementación

### Estrategia de Estado
**Opción elegida: `static` counters (simple, inicio)**
```c
static int total_tests = 0;
static int passed_tests = 0;
static int failed_tests = 0;
```
- **Ventaja**: Simplemente implementar
- **Desventaja**: No permite múltiples contextos
- **Refactor futuro**: Pasar a `fun_test_context_t` struct si escala

### Backward Compatibility
- Mantener `fun_method_name()` / `fun_free_str()` como deprecated
- Agregar advertencia en header: `__attribute__((deprecated))`
- Proporcionar alternativa en nuevos examples

### Testing de Cambios
Después de cada cambio, ejecutar:
```bash
make clean && make all
make test        # Verificar salida visual
make sane        # AddressSanitizer
make val         # Valgrind
```

---

## 📅 Roadmap Sugerido

| Semana | Fase | Tareas | Estado |
|--------|------|--------|--------|
| 1 | FASE 1 | 1.1 + 1.2 + 1.3 | ⬜ Pendiente |
| 2 | FASE 2 | 2.1 + 2.2 | ⬜ Pendiente |
| 3 | FASE 2 | 2.3 + Bug fixes | ⬜ Pendiente |
| 4+ | FASE 3 | 3.1 + 3.2 + 3.3 | ⬜ Pendiente |
