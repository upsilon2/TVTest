#ifndef TVTEST_RECORD_OPTIONS_H
#define TVTEST_RECORD_OPTIONS_H


#include "Options.h"
#include "Record.h"


namespace TVTest
{

	class CRecordOptions
		: public COptions
	{
		CFilePath m_SaveFolder;
		CFilePath m_FileName;
		bool m_fConfirmChannelChange;
		bool m_fConfirmExit;
		bool m_fConfirmStop;
		bool m_fConfirmStopStatusBarOnly;
		bool m_fAlertLowFreeSpace;
		unsigned int m_LowFreeSpaceThreshold;
		bool m_fShowRemainTime;
		int m_StatusBarRecordCommand;
		CRecordingSettings m_Settings;

		std::vector<String> m_WritePluginList;

	// CBasicDialog
		INT_PTR DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	public:
		enum {
			UPDATE_RECORDINGSETTINGS	= 0x00000001UL,
		};

		CRecordOptions();
		~CRecordOptions();

	// COptions
		bool Apply(DWORD Flags) override;

	// CSettingsBase
		bool ReadSettings(CSettings &Settings) override;
		bool WriteSettings(CSettings &Settings) override;

	// CBasicDialog
		bool Create(HWND hwndOwner) override;

	// CRecordOptions
		bool SetSaveFolder(LPCTSTR pszFolder);
		LPCTSTR GetSaveFolder() const { return m_SaveFolder.c_str(); }
		LPCTSTR GetFileName() const { return m_FileName.c_str(); }
		bool GetFilePath(LPTSTR pszFileName, int MaxLength) const;
		bool GenerateFilePath(LPTSTR pszFileName, int MaxLength, LPCTSTR *ppszErrorMessage = nullptr) const;
		bool ConfirmChannelChange(HWND hwndOwner) const;
		bool ConfirmServiceChange(HWND hwndOwner, const CRecordManager *pRecordManager) const;
		bool ConfirmStop(HWND hwndOwner) const;
		bool ConfirmStatusBarStop(HWND hwndOwner) const;
		bool ConfirmExit(HWND hwndOwner, const CRecordManager *pRecordManager) const;
		const CRecordingSettings &GetRecordingSettings() const { return m_Settings; }
		bool GetAlertLowFreeSpace() const { return m_fAlertLowFreeSpace; }
		ULONGLONG GetLowFreeSpaceThresholdBytes() const
		{
			return (ULONGLONG)m_LowFreeSpaceThreshold * (1024 * 1024);
		}
		bool IsTimeShiftRecordingEnabled() const { return m_Settings.m_fEnableTimeShift; }
		bool EnableTimeShiftRecording(bool fEnable);
		void SetShowRemainTime(bool fShow) { m_fShowRemainTime = fShow; }
		bool GetShowRemainTime() const { return m_fShowRemainTime; }
		int GetStatusBarRecordCommand() const { return m_StatusBarRecordCommand; }
	};

}	// namespace TVTest


#endif
