# Project B — CSV Mini Database & Query Engine

**CS351 AI 輔助軟體開發** · 元智大學資工系 · 黃士弦（s1113344）

以 CSV 檔案作為資料表，建置輕量查詢引擎：從載入、解析 SQL-like 查詢到在記憶體中執行 projection / selection / ordering / aggregation，並透過 CLI 輸出結果。

## 相關連結

| 項目 | 網址 |
|------|------|
| 課程總 repo | https://github.com/molong1230/11402_CS351 |
| 個人網站 | https://molong1230.github.io/ |
| Project 0 | https://github.com/molong1230/11402_CS351_Project0 |
| GitHub Actions | https://github.com/molong1230/11402_CS351_ProjectB/actions |

## 專案目標

- 將 CSV 解析為具 schema 的資料表
- 支援類 SQL 查詢語法（命令列 `--query`）
- 實作查詢管線：欄位投影、條件篩選、排序、筆數限制、基本聚合
- 對格式錯誤、未知欄位、不支援語法提供明確錯誤訊息
- 以單元／整合測試與 CI 確保行為可重現

## 主要功能

| 能力 | 說明 | 範例 |
|------|------|------|
| **SELECT** | 指定欄位或 `*` | `SELECT name,score` |
| **WHERE** | 等號條件篩選 | `WHERE class=A` |
| **ORDER BY** | 升冪 / 降冪排序 | `ORDER BY score DESC` |
| **LIMIT** | 限制回傳筆數 | `LIMIT 2` |
| **聚合** | 如 `COUNT(*)` | `SELECT COUNT(*) WHERE class=B` |

查詢字串需以 `SELECT` 開頭；CLI 透過 `csvdb_cli` 載入 CSV 並執行查詢。

## 專案結構

```
.
├── include/              # 標頭（CSV、查詢、引擎）
├── src/                  # 實作與 csvdb_cli 進入點
├── tests/                # 單元／整合測試
├── data/
│   └── sample_students.csv
├── docs/                 # 軟體文件（見下方索引）
├── CMakeLists.txt
└── .github/workflows/ci.yml
```

## 建置與執行

### 前置需求

- C++ 編譯器（g++ / clang++ / MSVC）
- CMake 3.16+

### Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### 執行測試

```bash
ctest --test-dir build --output-on-failure
```

### CLI 範例

Linux / macOS：

```bash
./build/csvdb_cli --csv data/sample_students.csv \
  --query "SELECT name,score WHERE class=A ORDER BY score DESC LIMIT 2"
```

Windows PowerShell：

```powershell
.\build\csvdb_cli.exe --csv data\sample_students.csv `
  --query "SELECT name,score WHERE class=A ORDER BY score DESC LIMIT 2"
```

## CI

GitHub Actions 工作流程：`.github/workflows/ci.yml`  
於 `push`、`pull_request` 時自動建置並執行 `ctest`。

## 開發歷程（摘要）

| 階段 | 內容 |
|------|------|
| WP-1 | 文件基礎（intended use、plan、SRS、SDS） |
| WP-2 | CMake 骨架、目錄配置、範例 CSV |
| WP-3 | CSV 載入、查詢解析、執行引擎（投影／篩選／排序／聚合） |
| WP-4 | CLI 參數與錯誤處理模型 |
| WP-5 | 單元／整合／驗收測試 |
| WP-6 | CI、部署說明、已知問題整理 |

詳細工作分解見 [`docs/01_plan.md`](docs/01_plan.md)。

## 技術亮點

- **模組化 C++**：parser、執行引擎、CLI 分層，便於測試與擴充
- **完整文件鏈**：SRS → SDS → 測試計畫 → 追溯矩陣
- **可重現驗證**：`data/sample_students.csv` + `ctest` + GitHub Actions

## 文件索引（`docs/`）

| 文件 | 說明 |
|------|------|
| [00_intended_use.md](docs/00_intended_use.md) | 使用情境與範圍 |
| [01_plan.md](docs/01_plan.md) | 實作計畫 |
| [02_SRS.md](docs/02_SRS.md) | 軟體需求規格 |
| [03_SDS.md](docs/03_SDS.md) | 軟體設計規格 |
| [04_test_plan.md](docs/04_test_plan.md) | 測試計畫 |
| [05_acceptance_tests.md](docs/05_acceptance_tests.md) | 驗收測試 |
| [06_traceability.md](docs/06_traceability.md) | 需求追溯 |
| [07_deploy.md](docs/07_deploy.md) | 建置與部署 |
| [08_known_issues.md](docs/08_known_issues.md) | 已知限制 |

## 學習目標（課程對照）

- 理解查詢系統從 **解析 → 執行 → 輸出** 的流程
- 練習在簡化環境中模擬 DBMS 核心行為（非完整 SQL、無並發寫入）
- 以測試與文件支撐可維護的專案交付

## 範圍外（Out of Scope）

- 完整 SQL 相容性
- 多使用者並發
- 超出 CSV 的持久化儲存

---

課程作業用途 · [molong1230](https://github.com/molong1230)
