# Foobar

CS_DllMain is a way to call a C# dll as if it were a C++ dll with DllMain.
For this the C++ DllMain calls a function of the C# dll.

## Usage

Well, edit this C# function

```c#
[DllExport]
public static void CS_DllMain() {
     MessageBox.Show("Bonjour from .NET Framework 4 :O");
     // Don't forget to run almost everything in a thread (avoid ui/thread blocking) !
}
```

## ❤️ Credits
[MonaLisa](https://github.com/HerMajestyDrMona)

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[GNU General Public License v3.0](https://github.com/EnergyCube/CS_DllMain/blob/main/LICENSE)
