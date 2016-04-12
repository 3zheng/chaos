CREATE TABLE [dbo].[online_time_detail]
(
	[Id] BIGINT NOT NULL PRIMARY KEY IDENTITY, 
    [user_id] BIGINT NOT NULL, 
    [ip_address] VARCHAR(50) NOT NULL, 
    [online_start_time] BIGINT NOT NULL, 
    [online_end_time] BIGINT NOT NULL, 
    [create_date] DATETIME NULL DEFAULT getdate(), 
    [plan_id] INT NOT NULL, 
    [match_id] BIGINT NOT NULL
)

GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'用户id',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'online_time_detail',
    @level2type = N'COLUMN',
    @level2name = N'user_id'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'ip地址',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'online_time_detail',
    @level2type = N'COLUMN',
    @level2name = N'ip_address'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'登录时间',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'online_time_detail',
    @level2type = N'COLUMN',
    @level2name = N'online_start_time'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'登出时间',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'online_time_detail',
    @level2type = N'COLUMN',
    @level2name = N'online_end_time'
GO
EXEC sp_addextendedproperty @name = N'MS_Description',
    @value = N'表记录创建时间',
    @level0type = N'SCHEMA',
    @level0name = N'dbo',
    @level1type = N'TABLE',
    @level1name = N'online_time_detail',
    @level2type = N'COLUMN',
    @level2name = N'create_date'