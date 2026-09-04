# C++ 回合制对战 Demo

基于 Windows、C++ 和 EasyX 的本地双人回合制游戏原型。包含角色选择、2 对 2 对战、普通攻击与技能、属性和 Buff 结算，以及胜负结算界面。

本仓库用于展示游戏逻辑开发与自动化回归测试实践，不是完整商业游戏，也不包含联网对战。

## 代码结构

- `game/inc/game`、`game/src/game`：角色、队伍、属性、伤害和 Buff 逻辑。
- `game/inc/ui`、`game/src/ui`：应用状态、界面切换、按钮交互。
- `game/inc/utils`、`game/src/utils`：图像及辅助功能。
- `game_tests`：Google Test 测试，直接编译相关生产代码进行验证。

## 构建与运行

已验证的配置为 **Visual Studio 2022 / MSVC v143 / Debug / x64**。

1. 安装 Visual Studio 2022 的“使用 C++ 的桌面开发”工作负载以及 Windows SDK。测试工程当前指定 SDK `10.0.26100.0`，如未安装，需要安装该版本或在 Visual Studio 中重定向到本机 SDK。
2. 安装适配 Visual Studio 2022 的 [EasyX](https://easyx.cn/)，确保编译器能找到 `easyx.h` 和对应库。
3. 打开 `game.sln`，还原 NuGet 程序包。测试依赖和版本记录在 `game_tests/packages.config` 中，不提交本地 `packages` 缓存。
4. 选择 `Debug | x64`，生成解决方案。
5. 将 `game` 设为启动项目，将调试工作目录设为 `$(ProjectDir)`；准备下文所列本地图像后运行。游戏内主要使用鼠标操作，按 `Q` 退出。

也可在 Visual Studio Developer PowerShell 中执行（先完成依赖安装和 NuGet 还原）：

```powershell
msbuild game.sln /t:Build /p:Configuration=Debug /p:Platform=x64 /m
Set-Location game
& ..\x64\Debug\game.exe
```

### 运行素材

公开仓库不分发原本使用的第三方角色图片。请自行准备有权使用的 PNG 图片，并放在以下位置：

```text
game/res/I0.png
game/res/I1.png
game/res/I2.png
game/res/I3.png
```

缺少这些文件时不能完整展示角色图像。上述文件已加入忽略规则，本地原素材不会被删除。依赖库和图片的使用、分发许可分别以各自权利人的条款为准。

## 自动化测试

在仓库根目录执行：

```powershell
& .\x64\Debug\game_tests.exe
& .\x64\Debug\game_tests.exe --gtest_shuffle --gtest_repeat=20 --gtest_break_on_failure
```

测试覆盖 Buff 插入、刷新与到期、容量和数组末槽边界、属性组合、物理与法术伤害、生命值下限，以及角色选择界面的按钮释放。

2026-09-04 在本地 Windows 开发环境验证：解决方案构建成功，24 个测试随机排序重复运行 20 轮全部通过。该结果不等同于跨机器构建验证或完整 GUI 自动化测试。

## 当前范围与限制

- 当前主要验证 `Debug | x64`，其他构建配置尚未逐一验证。
- 部分旧源码为 Windows 本地编码，编辑时应保留原编码，避免中文文本损坏。
- FMOD 音频相关文件为未接入当前构建的预留代码；运行当前版本不需要 FMOD。
- 本次仓库整理不改变游戏规则，不重写已有 Git 历史。
