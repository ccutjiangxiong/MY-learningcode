-- Keymaps are automatically loaded on the VeryLazy event
-- Default keymaps that are always set: https://github.com/LazyVim/LazyVim/blob/main/lua/lazyvim/config/keymaps.lua
-- Add any additional keymaps here
vim.g.mapleader = ' '
vim.g.maplocalleader = ' '
-- 安全删除映射
pcall(vim.keymap.del, 'n', '<leader>h', {buffer = 0})
pcall(vim.keymap.del, 'n', '<leader>l', {buffer = 0})
-- 设置新的映射
local opts = {noremap = true, silent = true}

vim.keymap.set('n', '<leader>h', 'd0', opts) -- 普通模式下删除到行首
vim.keymap.set('n', '<leader>l', 'd$', opts) -- 普通模式下删除到行尾

-- 跳转到下一个空行
function _G.jump_to_next_empty_line() vim.fn.search('^\\s*$', 'W') end

-- 跳转到上一个空行
function _G.jump_to_prev_empty_line() vim.fn.search('^\\s*$', 'bW') end

-- 映射
vim.api.nvim_set_keymap('n', '}', ':lua jump_to_next_empty_line()<CR>',
                        {noremap = true, silent = true})
vim.api.nvim_set_keymap('n', '{', ':lua jump_to_prev_empty_line()<CR>',
                        {noremap = true, silent = true})
vim.keymap.set("n", "<leader>rr", function()
    -- 获取当前文件名
    local filename = vim.fn.expand("%:p")
    filename = filename:gsub("/", "\\")
    local output_path = filename:gsub("%.cpp$", "")

    -- 保存当前文件
    vim.cmd("write")

    -- 需要执行的命令：编译后运行，并保持终端活跃等待输入
    local cmd = "g++ -std=c++20 -Wall \"" .. filename .. "\" -o \"" ..
                    output_path .. "\" && echo '--- 输出结果 ---' && \"" ..
                    output_path .. "\" && echo '按任意键继续...' && read"

    -- 使用 toggleterm 创建一个水平终端，用于编译和运行
    local term = require("toggleterm.terminal").Terminal:new({
        cmd = cmd,
        hidden = false,
        direction = "horizontal", -- 水平终端
        close_on_exit = false, -- 不要在退出时关闭（查看输出）
        start_in_insert = true -- 启动此窗口后直接进入 INSERT 模式
    })

    term:toggle() -- 打开终端

    -- 自动移动光标到新打开的水平终端窗口
    vim.cmd("wincmd j")
end)
return {}
