# Plan de Mejora: fun_testlib

## Objetivo
Transformar fun_testlib en una librería profesional e importable que permita a otros proyectos integrar un framework de testing simple y flexible, con soporte para tests unitarios sin complejidad innecesaria.

---

## 🔴 Fallos Actuales de Implementación

### 1. **Aserciones demasiado limitadas**
- Solo soporta `int` como tipo de dato
- `fun_assert_int` no retorna estado (void) → imposible automatizar resultados en CI/CD
- No hay contador de tests pasados/fallidos
- No hay forma de continuar después de una falla

**Impacto**: Tests solo sirven como verificación visual, no para automatización

### 2. **Gestión de memoria innecesaria**
- `fun_method_name()` requiere malloc/strcpy/free para un string literal
- Bug potencial: `malloc(len * sizeof(char*))` usa sizeof(char*) en lugar de sizeof(char)
- Patrones de uso obligan a users a gestionar memoria manualmente

**Impacto**: Código verboso, propenso a leaks, API poco amigable

### 3. **API verbosa y repetitiva**
- Test típico requiere 7 funciones por cada verificación:
  ```c
  fun_method_name() → fun_start() → fun_test_header() → fun_assert_int() → fun_color_show() → fun_end() → fun_free_str()
  ```
- Demasiado setup para un assert simple

**Impacto**: Barrera de entrada alta, tests más largos que el código a probar

### 4. **No hay estadísticas de tests**
- No hay manera de saber cuántos tests pasaron/fallaron
- No hay resumen final
- Imposible integrar en CI/CD (exit code siempre 0)

**Impacto**: No es viable para pipelines automatizados

### 5. **Límites en tipos de datos**
- Solo funciona con `int`
- Imposible testear strings, floats, structs, punteros
- `fun_assert_int_fun` está overcomplicated con va_list

**Impacto**: Limitada a casos de uso muy básicos

### 6. **Dependencia del contexto global**
- No hay forma de crear múltiples suites de tests independientes
- Todo es singletons con printf directo
- Imposible capturar output o redireccionar logs

**Impacto**: No escalable para proyectos medianos

### 7. **Configuración manual en cada proyecto**
- Cada proyecto que use la librería debe copiar `src-tests/` completo
- No hay template automático o generador
- Debe modificar Makefile manualmente (error-prone)

**Impacto**: Difícil onboarding para nuevos proyectos

---

## 💡 Puntos de Mejora (Priorizados)

> **VER**: [TASKS.md](./TASKS.md) para el checklist detallado de implementación con checkboxes.

### **FASE 1: Fundamentos (Essential)**

#### 1.1 Retorno de estado en aserciones
**Cambio**: Convertir asserts a que retornen `int` (1=OK, 0=KO)
```c
// Antes
void fun_assert_int(int orig, int new);

// Después  
int fun_assert_int(int orig, int new);
```
**Beneficio**: Permite contar resultados y retornar exit code correcto
**Complejidad**: Baja | **Impacto**: Alto

#### 1.2 Macro simplificador
**Cambio**: Crear macro `FUN_TEST()` que encapsule setup/teardown
```c
FUN_TEST("test_name", {
    FUN_ASSERT_INT(expected, actual);
    FUN_ASSERT_INT(expected2, actual2);
})
```
**Beneficio**: Reduce verbosidad de 7 líneas a 5
**Complejidad**: Media | **Impacto**: Alto

#### 1.3 Resumen de resultados
**Cambio**: Función `fun_tests_summary()` que imprima:
- Total de tests ejecutados
- Tests pasados/fallidos
- Exit code (0 si todos OK, 1 si fallos)
```c
fun_tests_summary();  // Prints: "Results: 5/7 passed"
return fun_tests_get_exit_code();
```
**Beneficio**: Compatible con CI/CD
**Complejidad**: Media | **Impacto**: Muy Alto

---

### **FASE 2: Flexibilidad (Important)**

#### 2.1 Aserciones genéricas para strings
**Cambio**: Agregar `fun_assert_str(const char *expected, const char *actual)`
```c
fun_assert_str("hello", my_string_function());
```
**Beneficio**: Testear funciones que retornan strings (común en C)
**Complejidad**: Baja | **Impacto**: Medio

#### 2.2 Aserciones para punteros NULL
**Cambio**: Agregar `fun_assert_ptr(void *ptr, int should_be_null)`
```c
fun_assert_ptr(malloc(10), 0);  // Expect non-NULL
fun_assert_ptr(NULL, 1);        // Expect NULL
```
**Beneficio**: Testing de allocations sin strcpy/malloc verbosity
**Complejidad**: Baja | **Impacto**: Medio

#### 2.3 Eliminar `fun_method_name()` / `fun_free_str()`
**Cambio**: Las macros manejan context internamente, sin user malloc
```c
// Antes
char *m = fun_method_name("test");
fun_start(m);
m = fun_free_str(m);

// Después  
FUN_TEST("test", { /* code */ })
```
**Beneficio**: Elimina surface de leaks, API más limpia
**Complejidad**: Alta (refactor) | **Impacto**: Muy Alto (DX improvement)

---

### **FASE 3: Integración (Nice-to-have)**

#### 3.1 Generator de template de tests
**Cambio**: Script `funtest-init.sh` que crea boilerplate
```bash
funtest-init my_project
# Genera: src-tests/Makefile, test.h, main_test.c, .gitignore
```
**Beneficio**: Onboarding rápido
**Complejidad**: Baja | **Impacto**: Bajo (UX)

#### 3.2 Soporte para test groups
**Cambio**: Agrupar tests relacionados y reportar por grupo
```c
FUN_GROUP("String Functions", {
    FUN_TEST("strlen", { ... })
    FUN_TEST("strcmp", { ... })
})
```
**Beneficio**: Mejor organización en suites grandes
**Complejidad**: Media | **Impacto**: Bajo

#### 3.3 Configuración de comportamiento
**Cambio**: Función para habilitar/deshabilitar colores, verbose, etc.
```c
fun_config_set(FUN_CFG_COLORS, 0);    // Disable colors
fun_config_set(FUN_CFG_VERBOSE, 1);   // Enable verbose
```
**Beneficio**: Mejor integración con IDEs, CI/CD
**Complejidad**: Media | **Impacto**: Bajo

---

## 📋 Recomendaciones de Implementación

### **Orden sugerido:**

1. **Primero (Semana 1)**: FASE 1.1-1.3
   - Retorno de estado + tracking
   - Resumen de resultados
   - Exit codes correctos
   - **Por qué**: Core functionality, habilita CI/CD

2. **Segundo (Semana 2)**: FASE 2.1-2.2
   - Aserciones para strings y punteros
   - Cubre 80% de casos de uso reales
   - **Por qué**: Extensibilidad sin complejidad

3. **Tercero (Semana 3)**: FASE 2.3
   - Refactor de macros para eliminar malloc verbosity
   - **Por qué**: Mejora DX, reduce bugs

4. **Opcional (Futuro)**: FASE 3
   - Generator, groups, config
   - **Por qué**: Nice-to-have, requiere más esfuerzo

---

## 🎯 Métricas de Éxito

| Métrica | Antes | Después |
|---------|-------|---------|
| Líneas por assert | ~10 | ~2 |
| Tipos soportados | int | int, str, ptr, + extensible |
| Compatible CI/CD | No | Sí |
| Setup proyecto nuevo | Manual (Makefile) | Automático (script) |
| Tests contables | No | Sí (pass/fail counts) |

---

## 🔄 Próximos Pasos Inmediatos

> **VER TAMBIÉN**: [TASKS.md](./TASKS.md) para tracking detallado con checkboxes.

1. **Crear rama**: `git checkout -b feature/improve-assertions`

2. **Arreglar bug crítico primero**:
   - [ ] Línea 24 en `src/ft_test_utils.c`: cambiar `sizeof(char*)` a `sizeof(char)`

3. **Implementar en orden FASE 1**:
   - Crear struct `fun_test_context_t` para tracking de estado
   - Modificar `fun_assert_int` para retornar `int` + incrementar contador
   - Implementar `fun_tests_summary()`
   - Crear macro `FUN_TEST()` en header

4. **Testing**: Ejecutar `make test` y verificar salida

5. **Documentar**: Actualizar AGENTS.md y README.md con nuevas APIs

6. **Validar**: Crear test file de ejemplo con todas las nuevas funciones

Ver [TASKS.md](./TASKS.md) para el checklist completo.

---

## 📝 Notas Importantes

- **Backward compatibility**: Las funciones viejas pueden seguir existiendo pero deprecadas
- **Bug a arreglar ahora**: `malloc(len * sizeof(char*))` en `fun_method_name()` → debe ser `sizeof(char)`
- **Considerar**: ¿Usar `static` counters o `context struct` para estado?
  - `static`: Más simple, pero menos flexible
  - `struct`: Más complejo, pero permite múltiples contexts
  - **Recomendación**: Empezar con `static`, refactor a struct si escala

