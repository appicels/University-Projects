// Helper function to trim the tooltip text
export default function (fullText, limit) {
	if(fullText.length > limit) {
		
		// Trim the string to the maximum length
		var trimmedText = fullText.substr(0, limit);
		
		// Re-trim if we are in the middle of a word
		trimmedText = trimmedText.substr(0, Math.min(trimmedText.length, trimmedText.lastIndexOf(" ")))
		
		return trimmedText + "...";
	} else {
		return fullText;
	}
}