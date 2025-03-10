vim.g.mapleader = ' '
vim.g.maplocalleader = ' '
-- 安全删除映射
pcall(vim.keymap.del, 'n', '<leader>h', { buffer = 0 })
pcall(vim.keymap.del, 'n', '<leader>l', { buffer = 0 })
-- 设置新的映射
local opts = { noremap = true, silent = true }

vim.keymap.set('n', '<leader>h', 'd0', opts)  -- 普通模式下删除到行首
vim.keymap.set('n', '<leader>l', 'd$', opts)  -- 普通模式下删除到行尾