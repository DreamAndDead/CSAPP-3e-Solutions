# gitbook-plugin-include

Preprocess your Markdown files, replacing all instances of

```
!INCLUDE "file.md"
```

with the contents of the specified file. The file can be a multi-level path.

## Usage

Add to your `book.json` plugin list:
```
{
    "plugins" : [ "include" ],
}
```



