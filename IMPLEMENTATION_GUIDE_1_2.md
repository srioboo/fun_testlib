# IMPLEMENTATION GUIDE: PHASE 1.2 - Function-Based Test API

## Objetivo
Simplificar la API de tests usando **funciones simples** en lugar de macros, manteniéndola clara, transparente y 100% conforme a la norma 42.

---

## 🎯 Problema Actual

Cada test requiere **7 líneas de setup/teardown**:

```c
char *m = fun_method_name("my_test");     // malloc/strcpy
fun_start(m);                               // print header
fun_test_header(1, 1);                      // print number
fun_assert_int(expected, actual);           // assert
fun_color_show();                           // legend
fun_end();                                  // footer
m = fun_free_str(m);                        // free
```

**Problema**: Verboso, propenso a memory leaks, API poco amigable.

---

## ✅ Solución: Funciones fun_test_start() y fun_test_end()

Almacenar el nombre del test en una **variable global estática** y usar dos funciones:

```c
// Almacena el nombre en g_current_test
void fun_test_start(const char *name);

// Libera g_current_test y limpia contexto
void fun_test_end(void);
```

**Nuevo flujo (3 líneas en lugar de 7)**:

```c
fun_test_start("my_test");
fun_assert_int(expected, actual);
fun_test_end();
```

---

## 📋 Implementación Paso a Paso

### **Paso 1: Actualizar `include/funtestlib.h`**

Agregar dos nuevas declaraciones (después de estructuras, antes de aserciones):

```c
/* Test lifecycle functions */
void        fun_test_start(const char *name);
void        fun_test_end(void);
```

**Ubicación**: Línea ~48, después de `ft_context_increment_wrapper` declaration.

### **Paso 2: Crear variable global en `src/ft_test_base.c`**

Agregar **una sola variable global estática** para almacenar el nombre del test actual:

```c
/* Global test context */
static char *g_current_test = NULL;
```

**Ubicación**: Después de los includes, antes de cualquier función.

### **Paso 3: Implementar fun_test_start() en `src/ft_test_base.c`**

```c
void	fun_test_start(const char *name)
{
	if (g_current_test)
		free(g_current_test);
	g_current_test = malloc(strlen(name) + 1);
	if (!g_current_test)
		return ;
	strcpy(g_current_test, name);
	fun_start(name);
	fun_test_header_label(name);
}
```

**Qué hace:**
- Libera test anterior si existe
- Almacena el nuevo nombre
- Llama a `fun_start()` automáticamente
- Llama a `fun_test_header_label()` con el nombre

### **Paso 4: Implementar fun_test_end() en `src/ft_test_base.c`**

```c
void	fun_test_end(void)
{
	fun_color_show();
	fun_end();
	if (g_current_test)
	{
		free(g_current_test);
		g_current_test = NULL;
	}
}
```

**Qué hace:**
- Imprime la leyenda de colores
- Imprime el footer
- Libera el nombre del test
- Limpia la variable

---

## 💻 Ejemplo Práctico: Refactor de test_ft_dummy.c

### **ANTES** (7 líneas por assert):
```c
void	test_ft_dummy(void)
{
	char *m = fun_method_name("ft_dummy");
	fun_start(m);
	fun_test_header(1, 1);
	fun_assert_int(42, 42);
	fun_color_show();
	fun_end();
	m = fun_free_str(m);
}
```

### **DESPUÉS** (3 líneas por assert):
```c
void	test_ft_dummy(void)
{
	fun_test_start("ft_dummy");
	fun_assert_int(42, 42);
	fun_test_end();
}
```

**Savings**: De 8 líneas a 3 líneas. Código más claro.

---

## 🔄 Casos de Uso Complejos

### Múltiples asserts en un test:

```c
void	test_string_functions(void)
{
	fun_test_start("string_functions");
	fun_assert_int(3, strlen("cat"));
	fun_assert_str("hello", "hello");
	fun_assert_int(0, strcmp("a", "a"));
	fun_test_end();
}
```

**Beneficio**: El nombre se imprime UNA sola vez al inicio, no repetido para cada assert.

### Tests secuenciales:

```c
void	test_suite(void)
{
	fun_test_start("test_one");
	fun_assert_int(1, 1);
	fun_test_end();
	
	fun_test_start("test_two");
	fun_assert_int(2, 2);
	fun_test_end();
	
	fun_test_start("test_three");
	fun_assert_int(3, 3);
	fun_test_end();
}
```

**Output esperado:**
```
[START] test_one
  [OK] 42 == 42
[END]

[START] test_two
  [OK] 2 == 2
[END]

[START] test_three
  [OK] 3 == 3
[END]

Results: 3/3 passed
```

---

## ✔️ Checklist de Implementación

- [ ] Agregar `void fun_test_start(const char *name);` a funtestlib.h
- [ ] Agregar `void fun_test_end(void);` a funtestlib.h
- [ ] Crear variable global `static char *g_current_test = NULL;` en ft_test_base.c
- [ ] Implementar `fun_test_start()` en ft_test_base.c
- [ ] Implementar `fun_test_end()` en ft_test_base.c
- [ ] Refactor test_ft_dummy.c para usar nuevo API
- [ ] Compilar: `make clean && make all`
- [ ] Verificar que norminette acepta cambios: `make norm`
- [ ] Ejecutar tests: `make test`
- [ ] Verificar salida con colores y contador de resultados
- [ ] Marcar PHASE 1.2 como [x] en TASKS.md

---

## 🧪 Testing de la Implementación

### Prueba 1: Compilación sin warnings
```bash
make clean && make all
# Debe compilar sin errores ni warnings
```

### Prueba 2: Norminette compliance
```bash
make norm
# No debe haber errores de norma
```

### Prueba 3: Ejecución de tests
```bash
make test
# Debe mostrar:
# - [START] test_ft_dummy
# - [OK] 42 == 42
# - [END]
# - Results: 1/1 passed
# - Exit code: 0
```

### Prueba 4: Memory leaks (opcional)
```bash
make sane
# Address sanitizer debe reportar 0 leaks
```

---

## 🎓 Por qué esta solución es mejor

| Aspecto | Macro | Función |
|---------|-------|---------|
| **Claridad** | Oculta lógica | Código visible |
| **Norma 42** | Riesgoso | ✅ 100% seguro |
| **Debugging** | Difícil | Fácil (breakpoints) |
| **Type safety** | No | ✅ Sí |
| **Mantenibilidad** | Compleja | Simple |

---

## 📝 Notas Importantes

1. **Variable global g_current_test**: Es la única forma de hacer esto sin pasar context como parámetro. Preferable a `struct` para PHASE 1.

2. **Memory management**: `fun_test_start()` y `fun_test_end()` manejan todo automáticamente. User nunca toca malloc/free.

3. **Backward compatibility**: Las funciones viejas (`fun_method_name`, `fun_start`, etc.) siguen disponibles para proyectos existentes.

4. **Línea de funciones**: Después de esta implementación, ft_test_base.c tendrá:
   - `fun_method_name()` (legacy)
   - `fun_free_str()` (legacy)
   - `fun_start()` (legacy)
   - `fun_end()` (legacy)
   - `fun_test_start()` (new)
   - `fun_test_end()` (new)
   
   Total: 6 funciones. Viola norma 42 (max 5 por file).
   **Solución**: Mover las legacy a ft_test_legacy.c O eliminarlas si no se usan más.

---

## 🚀 Próximos Pasos Después de PHASE 1.2

Una vez implementado esto:

1. **Verificar norminette** en todos los archivos
2. **Actualizar README.md** con el nuevo API
3. **Proceder a PHASE 2.1**: Agregar `fun_assert_str()`
4. **Proceder a PHASE 2.2**: Agregar `fun_assert_ptr()`

