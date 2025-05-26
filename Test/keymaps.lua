vim.g.mapleader = ' '
vim.g.maplocalleader = ' '
-- 安全删除映射
pcall(vim.keymap.del, 'n', '<leader>h', { buffer = 0 })
pcall(vim.keymap.del, 'n', '<leader>l', { buffer = 0 })
-- 设置新的映射
local opts = { noremap = true, silent = true }

vim.keymap.set('n', '<leader>h', 'd0', opts)  -- 普通模式下删除到行首
vim.keymap.set('n', '<leader>l', 'd$', opts)  -- 普通模式下删除到行尾

-- 跳转到下一个空行
function _G.jump_to_next_empty_line()
    vim.fn.search('^\\s*$', 'W')
end

-- 跳转到上一个空行
function _G.jump_to_prev_empty_line()
    vim.fn.search('^\\s*$', 'bW')
end

-- 映射
vim.api.nvim_set_keymap('n', '}', ':lua jump_to_next_empty_line()<CR>', { noremap = true, silent = true })
vim.api.nvim_set_keymap('n', '{', ':lua jump_to_prev_empty_line()<CR>', { noremap = true, silent = true })
