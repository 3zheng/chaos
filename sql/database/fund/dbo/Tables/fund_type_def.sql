CREATE TABLE [dbo].[fund_type_def]
(
	[fund_id] INT NOT NULL PRIMARY KEY, 
    [fund_type] INT NOT NULL, 
    [fund_name] NVARCHAR(50) NOT NULL, 
    [att_fund_id] INT NOT NULL DEFAULT 0, 
    [is_main_id] INT NOT NULL DEFAULT 0, 
    [is_outside_fund] INT NOT NULL DEFAULT 0
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'财富id 100以内保留，从101开始',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'fund_type_def',
    @level2type = N'COLUMN',
    @level2name = N'fund_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'财富类型，详情见type.proto的EnumFundType',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'fund_type_def',
    @level2type = N'COLUMN',
    @level2name = N'fund_type'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'财富名',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'fund_type_def',
    @level2type = N'COLUMN',
    @level2name = N'fund_name'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'财富定义表',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'fund_type_def',
    @level2type = NULL,
    @level2name = NULL
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'关联的fund_id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'fund_type_def',
    @level2type = N'COLUMN',
    @level2name = N'att_fund_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'0不是 1是 这个字段是和att_fund_id相关的，如果这个字段是1，就说明存在att_fund_id为当前fund_id的记录',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'fund_type_def',
    @level2type = N'COLUMN',
    @level2name = N'is_main_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'0不是 1是',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'fund_type_def',
    @level2type = N'COLUMN',
    @level2name = N'is_outside_fund'