# PawnPlus YSI Replacement

A collection of Pawn includes that replaces the most commonly used YSI modules with PawnPlus equivalents. Designed for open.mp and SA-MP servers running the modern Pawn compiler.

---

## Overview

YSI Core has two properties that make it difficult to use alongside PawnPlus:

- It reshuffles the AMX public function table during startup, which invalidates callback indices that PawnPlus registered earlier.
- It pulls in a large dependency graph even when a single module is needed.

This repository provides direct replacements for the four YSI modules used in most production gamemodes:

| YSI Module | Replacement |
|---|---|
| `YSI_Data\y_iterate` | `pp-foreach.inc` |
| `YSI_Coding\y_va` | `pp-va.inc` |
| `YSI_Coding\y_hooks` | `pp-hooks.inc` |
| Assorted YSI helper functions | `legacy-compat.inc` |

Each file is self-contained, requires only PawnPlus and open.mp headers, and preserves the original YSI surface so existing code continues to compile without call-site changes.

---

## Files

```
include/
    pp-foreach.inc
    pp-va.inc
    pp-hooks.inc
    legacy-compat.inc
```

Installation order in your gamemode:

```pawn
#include <open.mp>
#include <PawnPlus>

#include <pp-hooks>
#include <pp-foreach>
#include <pp-va>
#include <legacy-compat>
```

Remove all YSI includes after that.

---

## `pp-foreach.inc`

Replaces `YSI_Data\y_iterate` and standalone `foreach.inc`.

### Iterator declaration

| YSI | PawnPlus replacement |
|---|---|
| `new Iterator:Name<Size>;` | Same syntax, provided by `pp-foreach.inc` |
| `new IteratorArray:Name[Rows]<Size>;` | Same syntax, provided by `pp-foreach.inc` |
| `iterator Name<Size>` | Same syntax |

### Iterator operations

| YSI function | pp-foreach equivalent |
|---|---|
| `Iter_Add(iter, value)` | `Iter_Add(iter, value)` |
| `Iter_Remove(iter, value)` | `Iter_Remove(iter, value)` |
| `Iter_SafeRemove(iter, value, &next)` | `Iter_SafeRemove(iter, value, next)` |
| `Iter_Contains(iter, value)` | `Iter_Contains(iter, value)` |
| `Iter_Free(iter)` | `Iter_Free(iter)` |
| `Iter_Clear(iter)` | `Iter_Clear(iter)` |
| `Iter_Count(iter)` | `Iter_Count(iter)` |
| `Iter_Random(iter)` | `Iter_Random(iter)` |
| `Iter_Index(iter, index)` | `Iter_Index(iter, index)` |
| `Iter_Init(array)` | `Iter_Init(array)` |
| `Iter_Begin(iter)` | `Iter_Begin(iter)` |
| `Iter_End(iter)` | `Iter_End(iter)` |
| `Iter_Start(iter)` | `Iter_Start(iter)` |
| `Iter_Finish(iter)` | `Iter_Finish(iter)` |
| `Iter_First(iter)` | `Iter_First(iter)` |
| `Iter_Last(iter)` | `Iter_Last(iter)` |
| `Iter_Next(iter, slot)` | `Iter_Next(iter, slot)` |
| `Iter_Prev(iter, slot)` | `Iter_Prev(iter, slot)` |
| `Iter_Previous(iter, slot)` | `Iter_Previous(iter, slot)` |

### Iteration syntax

| YSI | pp-foreach |
|---|---|
| `foreach (new i : Player)` | Same syntax |
| `foreach (new v : Vehicle)` | Same syntax |
| `foreach (new a : Actor)` | Same syntax |
| `foreach (new i : CustomIterator)` | Same syntax |
| `foreach (i : AnyIterator)` | Same syntax without `new` |

### Built-in iterators

The following iterators are declared automatically:

- `Player` — connected players, updated via `OnPlayerConnect` and `OnPlayerDisconnect`.
- `Vehicle` — valid vehicles, updated via `CreateVehicle`, `AddStaticVehicle`, `AddStaticVehicleEx`, `DestroyVehicle`.
- `Actor` — valid actors, updated via `CreateActor`, `DestroyActor`.
- `Bot` — alias of `Player`.
- `NPC` — alias of `Player`.
- `Character` — alias of `Player`.

Tracking is installed through PawnPlus `pawn_register_callback` at gamemode init.

### PawnPlus-native macros

The following macros are provided in addition to classic `foreach` syntax. They do not require `Iterator:` declarations and iterate PawnPlus containers or plain loops directly.

| Macro | Purpose |
|---|---|
| `foreach_player(i)` | Iterate `IsPlayerConnected` slots |
| `foreach_vehicle(v)` | Iterate `IsValidVehicle` slots |
| `foreach_actor(a)` | Iterate `IsValidActor` slots |
| `foreach_list(list, item)` | Iterate a PawnPlus `List` |
| `foreach_map(map, key, value)` | Iterate a PawnPlus `Map` |
| `foreach_linked_list(list, item)` | Iterate a PawnPlus `LinkedList` |
| `foreach_pool(pool, item)` | Iterate a PawnPlus `Pool` |
| `foreach_arr(i, array)` | Iterate array by index |
| `foreach_arr_value(v, array)` | Iterate array by value |
| `foreach_count(i, N)` | Iterate `0` to `N - 1` |
| `foreach_range(i, start, end)` | Iterate `start` to `end - 1` |
| `foreach_down(i, start, end)` | Iterate `start` down to `end + 1` |

`break` and `continue` work inside every macro.

### Example

```pawn
new Iterator:MyDoors<500>;

Iter_Add(MyDoors, 5);
Iter_Add(MyDoors, 12);

if (Iter_Contains(MyDoors, 5))
{
    printf("Door 5 exists");
}

foreach (new id : MyDoors)
{
    printf("Door ID: %d", id);
}

foreach_player(i)
{
    SendClientMessage(i, 0xFFFFFFFF, "Hello");
}
```

### Limitations

- `IteratorArray:X[N]<M>` is declared but `Iter_Add(X[i], value)` on a specific row requires the row iterator to be passed by name. Multi-dimensional row access through macro expansion is not supported for values written via `Iter_Add`; use a `bool[][]` array or a PawnPlus `List` array instead.
- The classic `foreach` implementation relies on macro chaining that some older compilers cannot parse. Pawn compiler 3.10.11 and the community compiler 3.10.10+ handle it correctly.

---

## `pp-va.inc`

Replaces `YSI_Coding\y_va`.

### Provided functions

| Function | Description |
|---|---|
| `va_format(buffer[], size, format[], {Float,_}:...)` | Wrapper for open.mp `format` |
| `va_printf(format[], {Float,_}:...)` | Wrapper for open.mp `printf` |
| `String:va_format_s(format[], {Float,_}:...)` | Returns a PawnPlus `String` |
| `va_print_s(ConstStringTag:string)` | Wrapper for `print_s` |
| `va_SendClientMessage(playerid, colour, format[], {Float,_}:...)` | Formats then calls `SendClientMessage` |
| `va_SendClientMessageToAll(colour, format[], {Float,_}:...)` | Formats then calls `SendClientMessageToAll` |

### Migration from `y_va`

| YSI | pp-va |
|---|---|
| `stock Fn(playerid, const format[], va_list:args)` | `stock Fn(playerid, const fmt[], {Float,_}:...)` |
| `va_format(buf, size, format, args)` | `va_format(buf, size, fmt, ...)` |
| `va_printf(format, args)` | `va_printf(fmt, ...)` |
| `va_start<N>` | Replace with `...` at call site |
| `va_end(args)` | Remove |
| `va_arg(args, tag)` | Remove |

### Example

```pawn
va_SendClientMessage(playerid, 0xFFFFFFFF, "Welcome, %s. You have %d coins.", name, coins);
```

If a function must forward its variadic arguments to another user-defined function, format into a buffer first and pass the buffer. Pawn does not support forwarding `...` between user-defined functions.

### Limitations

- Requires a compiler that supports variadic forwarding. Pawn compiler 3.10.11 works. Old CompuPhase compilers fail with error 029.
- Functions receiving `{Float,_}:...` must not shadow the global `format` or `printf` symbol with a parameter of the same name. Use `fmt` or `format_str` instead.

---

## `pp-hooks.inc`

Replaces `YSI_Coding\y_hooks`.

### Hook syntax

| YSI | pp-hooks |
|---|---|
| `hook OnCallbackName(params)` | Same syntax |
| `hook native FunctionName(params)` | Same syntax |
| `hook ret OnCallbackName(&ret, params)` | Same syntax |

Hooks registered through `pp-hooks` are executed in registration order. Each hook must return a non-zero value to allow subsequent hooks to run.

### Public callback hooks

```pawn
hook OnPlayerConnect(playerid)
{
    SendClientMessage(playerid, 0xFFFFFFFF, "Welcome.");
    return 1;
}
```

### Native function hooks

```pawn
hook native SetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
    return SetPlayerPos(playerid, x, y, z + 0.1);
}
```

### Return-value modification

```pawn
hook ret OnPlayerUpdate(&ret, playerid)
{
    if (IsPlayerPaused(playerid))
    {
        ret = 0;
        return 1;
    }
    return 0;
}
```

### How hooks execute

`pp-hooks` uses PawnPlus `pawn_register_callback` for public callbacks and `pawn_add_hook` for native functions. The chain is managed by PawnPlus internals. If a callback returns zero, PawnPlus stops executing further handlers for that invocation.

### Compatibility with `y_hooks`

`pp-hooks` provides the same `hook` keyword and the same argument conventions. The internal `_ALS` mechanism that `y_hooks` uses is not present. Code that depends on `_ALS` macros directly (`_ALS_OnPlayerConnect`, etc.) must be adapted.

### Limitations

- Native hooking is implemented through `pawn_add_hook`, which routes through PawnPlus native interception. Libraries that also hook natives through different mechanisms may conflict. Register hooks for a given native from one mechanism only.
- `hook` does not currently support conditional hooking (hooks enabled or disabled at runtime). Register and unregister handlers through `pawn_register_callback` directly if that is required.

---

## `legacy-compat.inc`

Provides small helper functions that appear in YSI-adjacent codebases but have no direct PawnPlus equivalent.

| Function | Notes |
|---|---|
| `IsNumeric(const str[])` | Returns true if the string contains only digits |
| `IsNumericSigned(const str[])` | Allows a leading `+` or `-` |
| `IsNumericFloat(const str[])` | Allows one decimal point |
| `strcpy(dest[], const source[], maxlength)` | Alias for `strcopy` |
| `strncpy(dest[], const source[], maxlength)` | Alias for `strcopy` |
| `strcmp_old(str1, str2, bool:ignorecase, length)` | Alias for `strcmp` |

Include this file only if the compiler reports `undefined symbol` errors for the functions listed. Codebases that do not reference them do not need the include.

---

## Migration checklist

1. Install the PawnPlus plugin for the target server platform.
2. Copy the four include files into the compiler include path.
3. Add the includes in the order shown at the top of this document.
4. Remove every YSI include directive from the gamemode.
5. Compile and address errors:

### Common errors

**`undefined symbol "va_start"`**
A function still uses the YSI `y_va` variadic syntax. Refactor the function per the `pp-va` migration table: change `va_list:args` parameters to `{Float,_}:...` and `va_start<N>` to `...`.

**`array dimensions do not match` at `Iter_Init(X)`**
`X` is single-dimensional and does not require runtime initialisation. Remove the `Iter_Init` call.

**`function heading differs from prototype` in `y_va_header.inc`**
An extra `y_va` include is still present in the dependency graph. Locate it with a recursive search for `y_va` across `.inc` and `.pwn` files.

**`undefined symbol "foreach"`**
The file using `foreach` does not include `pp-foreach.inc` before that usage, or a `#define foreach` from another library shadows the macro. Add the include at the top of the affected file.

### Verify no YSI remains

Add the following block after all includes:

```pawn
#if defined _INC_y_va
    #error y_va is still included
#endif
#if defined _Y_ITERATE_LOCAL_VERSION
    #error y_iterate is still included
#endif
#if defined _INC_y_hooks
    #error y_hooks is still included
#endif
```

---

## Compiler requirements

| Compiler | Status |
|---|---|
| qawno 3.10.11 | Supported |
| Community compiler 3.10.10+ | Supported |
| open.mp compiler fork | Supported |
| CompuPhase 3.2.3664 | Not supported (no variadic forwarding) |

PawnPlus 1.5.3 or newer is required.

---

## Diagnostics

To inspect iterator and callback state at runtime, PawnPlus exposes:

- `pp_num_local_iters()`, `pp_num_global_iters()` — current iterator counts.
- `pp_num_tasks()` — outstanding async tasks.
- `pp_hook_strlen(bool:enable)` — debug hook for `strlen` misuse.

These are diagnostics from PawnPlus itself, not from this toolkit. They help verify that iterators are being created and released as expected.

---

## Directory layout

```
include/
    pp-foreach.inc
    pp-va.inc
    pp-hooks.inc
    legacy-compat.inc
```

---

## Credits

- **IS4** — PawnPlus.
- **Y_Less and contributors** — original YSI `foreach` algorithm, from which the iterator representation in `pp-foreach` is derived.

---

## License

Mozilla Public License 2.0.
